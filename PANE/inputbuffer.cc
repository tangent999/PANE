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

#include "inputbuffer.h"

Define_Module(inputbuffer);

void inputbuffer::initialize()
{
    // TODO - Generated method body
}

void inputbuffer::handleMessage(cMessage *msg)
{
    if(msg->arrivedOn("in"))
    {
        somemsg = check_and_cast<Packet *>(msg);
//        EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ "<<this->getFullName()<<":  Received, Message, ID: "<<somemsg->getPid()<<" \n";
        sendDelayed(somemsg,0.0,"out");
    }
    else if(msg->arrivedOn("Ack_in") && this->getIndex()==4)
    {
//        EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ "<<this->getFullName()<<": Received, Acknowledgement, ID: "<<ackmsg->getPid()<<" \n";
        msg = nullptr;
        delete msg;
    }
    else if(msg->arrivedOn("Ack_in"))
    {
        ackmsg = check_and_cast<Packet *>(msg);
//        EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ "<<this->getFullName()<<": Received, Acknowledgement, ID: "<<ackmsg->getPid()<<" \n";
        sendDelayed(ackmsg,0.0,"Ack_out");
    }
    else if(msg->arrivedOn("poll"))
    {
//        EV<<"~~~~~~~~~~~~~~~~~~~~~~~~~ "<<this->getFullName()<<": Received, Polling Request\n";
        sendDelayed(msg,0.0,"Ack_out");
    }
}
