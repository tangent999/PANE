//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "outputbuffer.h"

Define_Module(outputbuffer);

void outputbuffer::initialize()
{
    count=0;
}

void outputbuffer::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in"))
    {
        count++;
        somemsg = check_and_cast<Packet *>(msg);
//        EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ "<<this->getFullName()<<":  Received, Message, ID: "<<somemsg->getPid()<<" \n";
        sendDelayed(somemsg,0.0,"out");
    }
    else if(msg->arrivedOn("Ack_in"))
    {
        ackmsg = check_and_cast<Packet *>(msg);
//        EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ "<<this->getFullName()<<": Received, Acknowledgement, ID: "<<ackmsg->getPid()<<" \n";
        sendDelayed(ackmsg,0.0,"Ack_out");
    }
}
