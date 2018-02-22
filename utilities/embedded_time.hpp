#ifndef EMBEDDED_TIME__HPP
#define EMBEDDED_TIME__HPP


/** include files **/
#include <string> 
#include <ostream>
#include <cstdlib>

/** System call includes **/
#include "stringp.h"        // operator + int

/** definitions **/
typedef int  Hours ;
typedef int  Minutes ;
typedef int  Seconds ;
typedef int  MSeconds ;
typedef int  MicSeconds ;

using RTIME = int;

template<class Timer>
class EmbeddedTime {
  public:
    EmbeddedTime()
      : hour( 0 )
      , min( 0 )
      , sec( 0 )
      , msec( 0 )
      , micsec( 0 )
      { normalize(); }

    EmbeddedTime( Hours h , Minutes m , Seconds s , MSeconds ms , MicSeconds mics = 0)
      : hour( h )
      , min( m )
      , sec( s )
      , msec( ms )
      , micsec( mics)
      { normalize(); }
    
    EmbeddedTime( const std::string &t )
      { makeFrom(t); }

    EmbeddedTime( const RTIME micseconds )
      : hour( 0 )
      , min( 0 )
      , sec( 0 )
      , msec( 0 )
      , micsec( 0)
      { makeFrom( micseconds ); }
    
    EmbeddedTime( const EmbeddedTime<Timer> &t)
      : hour( t.hours() )
      , min( t.minutes() )
      , sec( t.seconds() )
      , msec( t.mseconds() )
      , micsec( t.micseconds() )
      {}

    static void initializeTimer() {
      Timer::initialize();
    };

    static EmbeddedTime<Timer> currentTime() {
      int micro_seconds = Timer::micro_seconds_since_started();
      return EmbeddedTime(micro_seconds);
    };

    // ** Modifiers ** //
    EmbeddedTime<Timer> &hours( const Hours & ) ;
    EmbeddedTime<Timer> &minutes( const Minutes & ) ;
    EmbeddedTime<Timer> &seconds( const Seconds & ) ;
    EmbeddedTime<Timer> &mseconds( const MSeconds & ) ;
    EmbeddedTime<Timer> &micseconds( const MicSeconds & ) ;

    // ** Queries ** // 
    const Hours    &hours() const ;
    const Minutes  &minutes() const ;
    const Seconds  &seconds() const ;
    const MSeconds &mseconds() const ;
    const MicSeconds &micseconds() const ;

    EmbeddedTime<Timer> operator +( const EmbeddedTime<Timer> &t ) const {
      if ( *this == EmbeddedTime<Timer>::Inf() || t == EmbeddedTime<Timer>::Inf() )
        
        return EmbeddedTime<Timer>::Inf();

      EmbeddedTime<Timer> st(
        hours() + t.hours(),
        minutes() + t.minutes(),
        seconds() + t.seconds(),
        mseconds() + t.mseconds(), 
        micseconds() + t.micseconds()
      );
      
      return st;
    }
 
    EmbeddedTime<Timer> operator -( const EmbeddedTime<Timer> &t ) const {
      if ( *this == EmbeddedTime<Timer>::Inf() || t == EmbeddedTime<Timer>::Inf() )
        return EmbeddedTime<Timer>::Inf();

      EmbeddedTime<Timer> st( hours() - t.hours(),
         minutes() - t.minutes(),
         seconds() - t.seconds(),
         mseconds() - t.mseconds(),
         micseconds() - t.micseconds() );

      return st; 
    }

    EmbeddedTime<Timer> &operator =( const EmbeddedTime<Timer> &t ) {
      hour = t.hours();
      sec = t.seconds();
      min = t.minutes();
      msec = t.mseconds();
      micsec = t.micseconds();
      return *this;
    }

    bool operator ==( const EmbeddedTime<Timer> &t ) const {
      return ( hours()    == t.hours()    &&
         minutes()  == t.minutes()  &&
         seconds()  == t.seconds()  &&
         mseconds() == t.mseconds()   &&
         micseconds() == t.micseconds() );
    }

    bool operator !=( const EmbeddedTime<Timer> &t ) const {
      return !((*this) == t);
    }

    EmbeddedTime<Timer> &operator =( const std::string &t ) // assignment operator
      {makeFrom(t); return *this;}
    
    EmbeddedTime<Timer> &operator -=( const EmbeddedTime<Timer> &t ) ;
    EmbeddedTime<Timer> &operator +=( const EmbeddedTime<Timer> &t ) ;

    bool operator <( const EmbeddedTime<Timer> &t ) const {
      return( hours() < t.hours()    ||
            ( hours() == t.hours() &&
             ( minutes() < t.minutes()  ||
              ( minutes() == t.minutes()  &&
                ( seconds() < t.seconds() ||
                 ( seconds() == t.seconds() &&
                  ( mseconds() < t.mseconds() ||
                   ( mseconds() == t.mseconds() &&
                     micseconds() < t.micseconds() ) ) ) ) ) ) ) ) ;
    }

    bool operator >( const EmbeddedTime<Timer> &t ) const {
      return !((*this) <= t);
    }

    bool operator >=( const EmbeddedTime<Timer> &t ) const {
      return !((*this) < t);
    }
    bool operator <=( const EmbeddedTime<Timer> &t ) const {
      return (((*this) < t)||((*this) == t));
    }

    std::string asString() const {
      char buf[100];

      if (*this == EmbeddedTime<Timer>::Inf())
        sprintf( buf, "..." );
      else
        sprintf( buf, "%02d:%02d:%02d:%03d:%03d", hours(), minutes(), seconds(), mseconds(), micseconds() );

      return std::string( buf );
    }

    long long asMsecs() const
      { return mseconds() + seconds() * 1000 + minutes() * 60000 + hours() * 3600 * 1000; }

    long long asMicsecs() const
      { return micseconds() + mseconds() * 1000 + seconds() * 1000 * 1000 + minutes() * 60000 * 1000 + hours() * 3600 * 1000 * 1000; }

    static const EmbeddedTime<Timer> Zero ;
    static const EmbeddedTime<Timer> Inf()  ;
    
  private:
    Hours hour  ;
    Minutes min ;
    Seconds sec ;
    MSeconds msec ;
    MicSeconds micsec ;
    
    EmbeddedTime<Timer> &makeFrom( const std::string &str ) {
      sscanf( str.c_str(), "%d:%d:%d:%d", &hour, &min, &sec, &msec); micsec = 0;
      normalize();
      return *this;
    }

  public:
    EmbeddedTime<Timer> &makeFrom( RTIME xentime ) {
      RTIME mictime = xentime; // need to divide by 1000 if using Xenomai
      minutes( static_cast< int >( mictime/ (1000*1000*60) ) ) ;
      mictime -= (minutes()*1000*1000*60);
      seconds( static_cast< int >( mictime/(1000*1000) ) ) ;
      mictime -= (seconds()*1000*1000);
      mseconds( static_cast< int >( mictime/1000) );
      mictime -= (mseconds()*1000);
      micseconds(static_cast< int >( mictime));
      normalize() ;
      return *this ;
    }

    EmbeddedTime<Timer> &normalize() {
      // 0..999 Microseconds
      adjust( micsec, msec , 1000 );

      // 0..999 Miliseconds
      adjust( msec, sec , 1000 );

      // 0..59 seconds
      adjust( sec , min , 60   );

      // 0..59 minutes
      adjust( min , hour, 60   );

      return *this ;
    }

    EmbeddedTime<Timer> &adjust( int &left, int &right, int maxVal ) {
      if( left >= maxVal )
      {
        right += left / maxVal ;
        left %= maxVal ;
      } else if( left < 0 )
      {
        register int aux = std::abs( left / maxVal ) + ( left % maxVal == 0 ? 0 : 1 );
        right -= aux ;
        left += maxVal * aux ;
      }
      return *this ;
    }
};

/** Public data **/
template<class Timer> const EmbeddedTime<Timer> EmbeddedTime<Timer>::Zero;

template<class Timer> const EmbeddedTime<Timer> EmbeddedTime<Timer>::Inf() {
  return EmbeddedTime( 32767, 59, 59, 999, 999) ;}  // Infinity constant 

/** inline methods **/
template<class Timer> inline const Hours &EmbeddedTime<Timer>::hours() const {
  return hour ;
}

template<class Timer> inline const Minutes &EmbeddedTime<Timer>::minutes() const {
  return min ;
}

template<class Timer> inline const Seconds &EmbeddedTime<Timer>::seconds() const {
  return sec ;
}

template<class Timer> inline const MSeconds &EmbeddedTime<Timer>::mseconds() const {
  return msec ;
}

template<class Timer> inline const MicSeconds &EmbeddedTime<Timer>::micseconds() const {
  return micsec ;
}

template<class Timer> inline EmbeddedTime<Timer> &EmbeddedTime<Timer>::hours( const Hours &h ) {
  hour = h ;
  return *this ;
}

template<class Timer> inline EmbeddedTime<Timer> &EmbeddedTime<Timer>::minutes( const Minutes &m ) {
  min = m ;
  normalize() ;
  return *this ;
}

template<class Timer> inline EmbeddedTime<Timer> &EmbeddedTime<Timer>::seconds( const Seconds &s ) {
  sec = s ;
  normalize() ;
  return *this ;
}

template<class Timer> inline EmbeddedTime<Timer> &EmbeddedTime<Timer>::mseconds( const MSeconds &ms ) {
  msec = ms ;
  normalize() ;
  return *this ;
}

template<class Timer> inline EmbeddedTime<Timer> &EmbeddedTime<Timer>::micseconds( const MicSeconds &mics ) {
  micsec = mics ;
  normalize() ;
  return *this ;
}

template<class Timer> inline EmbeddedTime<Timer> &EmbeddedTime<Timer>::operator -=( const EmbeddedTime<Timer> &t ) {
  (*this) = (*this) - t ;
  return *this ;
}

template<class Timer> inline EmbeddedTime<Timer> &EmbeddedTime<Timer>::operator +=( const EmbeddedTime<Timer> &t ) {
  (*this) = (*this) + t ;
  return *this ;
}

template<class Timer> inline std::ostream &operator <<( std::ostream &os, const EmbeddedTime<Timer> &t ) {
  os << t.asString();
  return os;
}

#endif // EMBEDDED_TIME__HPP

