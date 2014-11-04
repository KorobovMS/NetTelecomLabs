#ifndef DATAGRAMPROCESSOR_H
#define DATAGRAMPROCESSOR_H

class QByteArray;
class WritersStorage;
class FilterStorage;

class DatagramProcessor
{
public:
    DatagramProcessor();
    void Process(const QByteArray& datagram);
    ~DatagramProcessor();

private:
    WritersStorage* writers_;
    FilterStorage* filters_;
};

#endif // DATAGRAMPROCESSOR_H
