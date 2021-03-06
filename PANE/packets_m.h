//
// Generated file, do not edit! Created by nedtool 5.1 from packets.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __PACKETS_M_H
#define __PACKETS_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>packets.msg:2</tt> by nedtool.
 * <pre>
 * message Packet
 * {
 *     //    char data[9];
 *     int pid;			//Sequential numbers. PID for a packet and its ACK is the same
 *     int hid;			//Identifies the PID of its head
 *     double delay;		//Total Time taken to travel from source to the sink. Reset delay when ACK is generated
 *     int packet_type;		//0 = Data, 1 = ACK, 4 = Poll
 *     int size;			//Size of the packet
 * }
 * </pre>
 */
class Packet : public ::omnetpp::cMessage
{
  protected:
    int pid;
    int hid;
    double delay;
    int packet_type;
    int size;

  private:
    void copy(const Packet& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const Packet&);

  public:
    Packet(const char *name=nullptr, short kind=0);
    Packet(const Packet& other);
    virtual ~Packet();
    Packet& operator=(const Packet& other);
    virtual Packet *dup() const override {return new Packet(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getPid() const;
    virtual void setPid(int pid);
    virtual int getHid() const;
    virtual void setHid(int hid);
    virtual double getDelay() const;
    virtual void setDelay(double delay);
    virtual int getPacket_type() const;
    virtual void setPacket_type(int packet_type);
    virtual int getSize() const;
    virtual void setSize(int size);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Packet& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Packet& obj) {obj.parsimUnpack(b);}


#endif // ifndef __PACKETS_M_H

