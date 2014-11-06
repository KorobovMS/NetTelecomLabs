#ifndef DATAGRAMPROCESSOR_H
#define DATAGRAMPROCESSOR_H

class QByteArray;
class QString;
class WritersStorage;
class FilterStorage;

/**
 * @brief The DatagramProcessor class controls datagram parsing, filters them
 *        and writes them to sources
 */
class DatagramProcessor
{
public:
    DatagramProcessor();
    bool Initialize(const QString& settings_file);
    void Process(const QByteArray& datagram);
    ~DatagramProcessor();

private:
    bool is_initialized_;
    WritersStorage* writers_;
    FilterStorage* filters_;
};

#endif // DATAGRAMPROCESSOR_H
