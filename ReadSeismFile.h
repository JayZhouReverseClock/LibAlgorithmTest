#ifndef READSEISMFILE_H
#define READSEISMFILE_H

#include "QComTools.h"
#include <QFile>
#include <QList>
#include <QByteArray>
#include <QVector>
#include <QThread>
#include <QDebug>

class ReadSeismFile : public QThread
{
    Q_OBJECT
public:
    ReadSeismFile();
    ~ReadSeismFile();
    void SetFilePath(const QString &file_path);
    void SetParams(const unsigned int ch_num, const int sp_rate, const double sp_time);
    void run();
    void Set3BFormat();
    QList<double *> GetSeismData();
    int GetSeismLen();
    float* testdata;

    double *GetCurrentSeismData() const;

private:
    void InitReadStore();
    void DestoryReadStore();
    void Read4BData();
    void Read3BData();
    //int GetSeismLen();
    int Cvt3B2Int(char *data);
    float Cvt3B2Float(unsigned char *data);


signals:
    void ReadFinished(double *data);
    void ReadErr(QString err_info);
    void ReadProcessPercent(int precent);

private:
    unsigned int ch_num;
    double sp_rate;
    double sp_time;
    QString file_path;

    QList<double *> read_store;
    int curr_store_index;
    bool is_3b_format;
    double *m_current_seism_data;
};

#endif // READSEISMFILE_H
