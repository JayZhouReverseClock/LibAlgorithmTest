#include "ReadSeismFile.h"

ReadSeismFile::ReadSeismFile() :
    ch_num(0), sp_rate(0), sp_time(0),
    file_path(""), curr_store_index(0), read_store()
{
    is_3b_format = true;
}
ReadSeismFile::~ReadSeismFile()
{
    qDeleteAll(read_store);
}

void ReadSeismFile::SetFilePath(const QString &file_path)
{
    this->file_path = file_path;
}
// sp_rate: 1000, sp_tim: 4.096
void ReadSeismFile::SetParams(const unsigned int ch_num, const int sp_rate, const double sp_time)
{
    DestoryReadStore();
    if(this->ch_num * this->sp_rate * this->sp_time !=
            ch_num * sp_rate * sp_time)
    {
        this->ch_num = ch_num;
        this->sp_rate = sp_rate;
        this->sp_time = sp_time;
    }
    InitReadStore();
}

void ReadSeismFile::run()
{
    m_current_seism_data = nullptr;
    is_3b_format = false;
    if(is_3b_format)
    {
        Read3BData();
    }else{
        Read4BData();
    }
}

QList<double *> ReadSeismFile::GetSeismData()
{
    return read_store;
}

void ReadSeismFile::InitReadStore()
{
    for(int i = 0; i < 2; i++)
    {
        double *data = new double[(int)(sp_rate * sp_time) * ch_num]{0};
        read_store.push_back(data);
    }
}

void ReadSeismFile::DestoryReadStore()
{
    qDeleteAll(read_store.begin(), read_store.end());
    read_store.clear();
}

void ReadSeismFile::Read4BData()
{
    float *tmp = new float[GetSeismLen()]{0};

    QFile file(file_path);
    if(!file.exists() || (file.size() != (GetSeismLen() * 4)))
    {
        emit ReadErr("Read failed");
        delete tmp;
        return;
    }
    if(QComTools::ReadSeismDataFromFile(file_path, sp_rate, sp_time, tmp) < 0)
    {
        emit ReadErr("Read failed");
        delete tmp;
        return;
    }
//    if((file.read((char*)tmp, file.size())) != file.size())
//    {
//        emit ReadErr(tr("Read data from file failed."));
//        file.close();
//        return;
//    }
    for(int i = 0; i < GetSeismLen(); i++)
    {
        read_store[0][i] = (double)tmp[i];
    }

    emit ReadFinished(read_store.first());
    m_current_seism_data = read_store.first();
    read_store.move(0, read_store.size() - 1);
    //delete tmp;
    testdata = tmp;
}

void ReadSeismFile::Read3BData()
{
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Unbuffered))
    {
        emit ReadErr(tr("Read seism file failed. [file path: %1]").arg(file_path));
        return;
    }

    if(file.size() != GetSeismLen()*3)
    {
        emit ReadErr(tr("File len[%1 Bytes] is not same as config[%2 Bytes].").arg(file.size()).arg(GetSeismLen() * sizeof(int)));
        file.close();
        return;
    }
//    file.seek(41);
    qDebug()<<GetSeismLen();
    char *tmp_data = new char[GetSeismLen()*3]{0};
    if((file.read(tmp_data, GetSeismLen()*3)) != GetSeismLen()*3)
    {
        emit ReadErr(tr("Read data from file failed."));
        file.close();
        return;
    }

    for(int i = 0; i < GetSeismLen(); i++)
    {
        // 如果使用(char *)tmp_data 数据回异常
//        qDebug()<<Cvt3B2Float((unsigned char *)tmp_data + i * 3);
        read_store[0][i] = (double)Cvt3B2Float((unsigned char *)tmp_data + i * 3);
    }

    for(int i = 0; i < (int)(sp_rate * sp_time); i++)
    {
//        read_store[0][i] = 100 * sin(i * 0.1);
    }


    emit ReadFinished(read_store.first());
    read_store.move(0, read_store.size() - 1);
    file.close();
    delete tmp_data;
}

int ReadSeismFile::GetSeismLen()
{
    return int(ch_num * sp_rate * sp_time);
}

int ReadSeismFile::Cvt3B2Int(char *data)
{
    int tmp = 0;
    if(*(data) & 0x80)
    {
        tmp = ((0xFF000000 | (*(data + 0) << 16) | (*(data + 1) << 8) | (*(data + 2))));
    }else{
        tmp = (0x00000000 | (*(data + 0) << 16) | (*(data + 1) << 8) | (*(data + 2)));
    }
    return tmp;
}

float ReadSeismFile::Cvt3B2Float(unsigned char *data)
{
    int tmp = 0;
    if(*(data) & 0x80)
    {
        tmp = ((0xFF000000 | (*(data + 0) << 16) | (*(data + 1) << 8) | (*(data + 2))));
    }else{
        tmp = (0x00000000 | (*(data + 0) << 16) | (*(data + 1) << 8) | (*(data + 2)));
    }
    return (float)tmp;
}

double *ReadSeismFile::GetCurrentSeismData() const
{
    return m_current_seism_data;
}
