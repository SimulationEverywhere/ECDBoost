/**
 * Copyright (c) 2015, Daniella Niyonkuru
 * Carleton University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef ECDBOOST_SIMULATION_PDEVS_PORT_H
#define ECDBOOST_SIMULATION_PDEVS_PORT_H

#include <ecdboost/simulation/model.hpp>

namespace ecdboost {

/**
 * @brief The pdevs::port class is the base of all top hardware ports.
 *
 * The port class has one functions that needs to be implemented by a user to be used.
 * The Driver object instantiates the port model and calls pDriver
 * during execution.
 */

template <class TIME, class MSG>
class port : public model<TIME>
{
public:
    using time_type=TIME;
    using message_type=MSG; //Message suggested for embedded execution is eMessage
    using model_type=port<TIME, MSG>;
    using CONTENT = typename MSG::inner_type;

    port(const std::string &name) noexcept :portName( name ), pollingPeriod( TIME(0,0,0,0) ) {}
    port(const std::string &name, const TIME &pollingP) noexcept :portName( name ), pollingPeriod( pollingP ) {}
    virtual ~port(){}
    /**
     * @brief pDriver converts received signals into hardware commands or vice-versa - To be implemented by the user
     */
    virtual bool pDriver(CONTENT&) const noexcept = 0;
    /**
     * @brief asString returns the name of the port
     */
	const std::string asString() const { return portName; }
    /**
     * @brief print prints the name of the port - To be implemented by the user
     */
	virtual void print() noexcept = 0;
    /**
     * @brief getPollingPeriod returns the polling period - Needed for input ports
     */
	const TIME getPollingPeriod() const { return pollingPeriod; }



protected:
    std::string portName;
    TIME pollingPeriod;
    //std::shared_ptr<model<TIME>> connectedModel; //to be included later
    //Port( const std::string & , const ModelId & ) ;  // Default constructor
};

}  // Closing namespace

#endif  // ECDBOOST_SIMULATION_PDEVS_PORT_H

