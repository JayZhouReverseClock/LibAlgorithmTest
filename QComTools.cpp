#include "QComTools.h"

int QComTools::CvtMsb3Byte2Int(const unsigned char *data)
{
    // 最高bit为1表示负数
    return ((*(data) & 0x80) == 0x00) ?
                (0x00000000 | (*(data + 0) << 16) | (*(data + 1) << 8) | (*(data + 2)))
              : ((0xFF000000 | (*(data + 0) << 16) | (*(data + 1) << 8) | (*(data + 2))));
}

float QComTools::CvtMsb3Byte2Float(const unsigned char *data)
{
    return ((*(data) & 0x80) == 0x00) ?
                (float)((int)(0x00000000 | (*(data + 0) << 16) | (*(data + 1) << 8) | (*(data + 2))))
              : (float)((int)(0xFF000000 | (*(data + 0) << 16) | (*(data + 1) << 8) | (*(data + 2))));
}

QByteArray QComTools::HexStr2HexStr(const QString &str, bool *ok)
{
    QByteArray params;
    if(str.isEmpty())
        goto CvtFailed;

    {
        QStringList args_list = str.trimmed().split(QRegExp("[ ,]"), QString::SkipEmptyParts);
        for(QStringList::iterator itor = args_list.begin(); itor != args_list.end(); itor++)
        {
            QString args = *itor;

            bool item_ok = false;
            uint temp = args.toUInt(&item_ok, 16);
            if((!item_ok) || ((temp >> 8) != 0))
                goto CvtFailed;
            params.push_back((temp & 0xFF));
        }
        ;
    }
    goto CvtSuccess;

CvtFailed:
    if(ok != nullptr)
        *ok = false;
    return QByteArray();

CvtSuccess:
    if(ok != nullptr)
        *ok = true;
    return params;
}

QString QComTools::HexData2HexStr(const unsigned char *data, const int len, const bool with_space_splite)
{
    QString hex_str;
    hex_str.reserve(with_space_splite ? len * 3 - 1 : len * 2);

    for(int i = 0; i < len; i++)
    {
        hex_str += QString("%1%2").arg(*(data + i), 2, 16, QChar('0'))
                   .arg(with_space_splite ? " " : "");
    }
    return hex_str.toUpper();
}

QString QComTools::CurrDateTimeTag(QComTools::DateTimeTagFormat type)
{
    switch (type) {
        case DateTimeTagFormat::FullWithUnderLineSplite:
        {
            return QDateTime::currentDateTime().toString("yyyyMMdd_hhmmsszzz");
        }
        case DateTimeTagFormat::NormalFull:
        {
            return QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz");
        }
        case DateTimeTagFormat::NormalDateOnly:
        {
            return QDateTime::currentDateTime().toString("yyyy/MM/dd");
        }
        case DateTimeTagFormat::NormalTimeMin:
        {
            return QDateTime::currentDateTime().toString("mm:ss");
        }
        case DateTimeTagFormat::NormalTimeOnly:
        {
            return QDateTime::currentDateTime().toString("hh:mm:ss");
        }
        case DateTimeTagFormat::NormalTimeWithMinSec:
        {
            return QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
        }
    }
    return QString("");
}

void QComTools::CvtMsbHexData2Float(const unsigned char *sour, float *dest, const unsigned int sp_num)
{
    for(int i = 0; i < (int)sp_num; i++)
    {
        *(dest++) = CvtMsb3Byte2Float(sour);
        sour += 3;
    }
}

void QComTools::CvtMsbHexData2Int(const unsigned char *sour, int *dest, const unsigned int sp_num)
{
    for(int i = 0; i < (int)sp_num; i++)
    {
        *(dest++) = CvtMsb3Byte2Int(sour);
        sour += 3;
    }
}

bool QComTools::WriteData2File(QFile *file, const char *data, const int len)
{
    if(file == nullptr)
        return false;
    int left_len = len;
    int ret = 0;
    while(left_len > 0)
    {
        ret = file->write(data, left_len);
        if(ret < 0)
            return false;
        left_len -= ret;
        data += ret;
    }
    return true;
}

void QComTools::CvtFloat2MsbHexData(const float *sour, unsigned char *dest, const unsigned int sp_num)
{
    const unsigned char *temp = (const unsigned char*)sour;
    for(int i = 0; i < (int)sp_num; i++)
    {
        *(dest++) = *(temp + 3);
        *(dest++) = *(temp + 2);
        *(dest++) = *(temp + 1);
        *(dest++) = *(temp + 0);
    }
}

void QComTools::CvtInt2MsbHexData(const int *sour, unsigned char *dest, const unsigned int sp_num)
{
    const unsigned char *temp = (const unsigned char*)sour;
    for(int i = 0; i < (int)sp_num; i++)
    {
        *(dest++) = *(temp + 3);
        *(dest++) = *(temp + 2);
        *(dest++) = *(temp + 1);
        *(dest++) = *(temp + 0);
    }
}

bool QComTools::WriteData2File(QFile *file, const QString &data)
{
    return WriteData2File(file, data.toStdString().c_str(), data.size());
}

QFile *QComTools::CreateAndOpenTextFile(const QString &file_path)
{
    QFile *file = new QFile(file_path);
    if(file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return file;
    }else{
        delete file;
        return nullptr;
    }
}

QFile *QComTools::CreateAndOpenDataFile(const QString &file_path)
{
    QFile *file = new QFile(file_path);
    if(file->open(QIODevice::WriteOnly | QIODevice::Unbuffered))
    {
        return file;
    }else{
        delete file;
        return nullptr;
    }
}

bool QComTools::CreateDir(const QString &dir_path)
{
    QString temp_path_str = dir_path;
//    // 是否是绝对路径
//    bool is_abs_path = PathStrIsAbsPath(dir_path);
//    if(!is_abs_path)
//    {
//        temp_path_str = QDir(".").absolutePath() + dir_path;
//    }
    QDir dir(temp_path_str);
    if(dir.exists())
    {
        return true;
    }else{
        return dir.mkpath(".");
    }
}

bool QComTools::DelDir(const QString &dir_path)
{
    QDir dir(dir_path);
    if(!dir.exists()){
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo file, fileList){
        if (file.isFile()){
            file.dir().remove(file.fileName());
        }else{
            DelDir(file.absoluteFilePath());
        }
    }
    return dir.rmpath(dir.absolutePath());
}

bool QComTools::ReCreateDir(const QString &dir_path)
{
    if(DelDir(dir_path))
    {
        return CreateDir(dir_path);
    }
    return false;
}

bool QComTools::PathStrIsAbsPath(const QString &path)
{
    bool is_abs = false;
#ifdef Q_OS_WIN
    if(path.contains(":"))
        is_abs = true;
#else
    if(path.startsWith("/"))
        is_abs = true;
#endif
    return is_abs;
}

QRegExp QComTools::IpRegExp()
{
    return QRegExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
}

qintptr QComTools::GetObjPtrValue(const void *obj)
{
    return qintptr(obj);
}

void QComTools::MoveObjectToThreadListAndStart(QObject *object, QMap<qintptr, QThread *> &thread_list)
{
    qintptr key = GetObjPtrValue(object);
    if(thread_list.contains(key))
    {
        if(!thread_list[key]->isRunning())
        {
            thread_list[key]->start();
        }
    }else{
        thread_list[key] = new QThread;
        object->moveToThread(thread_list[key]);
        thread_list[key]->start();
    }
}

void QComTools::MoveOutObjectFromThreadList(const QObject *object, QMap<qintptr, QThread *> &thread_list)
{
    qintptr key = GetObjPtrValue(object);
    if(thread_list.contains(key))
    {
       thread_list[key]->quit();
       thread_list[key]->deleteLater();
       thread_list.remove(key);
    }
}

QString QComTools::Hex2Str(const unsigned char *data, const int len)
{
    QString result = "";
    result.reserve(len * 3);
    for(int i = 0; i < len; i++)
    {
        result += QString("%1 ").arg((data[i]), 2, 16, QChar('0'));
    }
    return result;
}

void QComTools::ReleaseFile(QFile *&file)
{
    if(file != nullptr)
    {
        file->close();
        delete file;
        file = nullptr;
    }
}

int QComTools::ReadSeismDataFromFile(const QString &file_path, const int sp_rate, const double sp_time, float *data)
{
    int read_point_num = 0;
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Unbuffered))
        return -1;
    int per_ch_point_num = (int)(sp_rate * sp_time);
    if(file.size() % (per_ch_point_num * 4) != 0)
    {
        qDebug()<<QString("file size[%1 byte] not right with acq params[sp rate: %2 Hz, sp time: %3 s]").arg(file.size())
                  .arg(sp_rate).arg(sp_time);
        return -2;
    }

    QByteArray file_data = file.readAll();
    if(file_data.size() != file.size())
    {
        qDebug()<<"read err";
        return -3;
    }


    for(int i = 0; i < file_data.size();)
    {
        data[read_point_num++] = CvtMsb4Byte2Float((unsigned char *)(file_data.data() + i)) * 2500.0 / 8388608;
        i += 4;
    }
    return read_point_num * 4;
}

float QComTools::CvtMsb4Byte2Float(const unsigned char *data)
{
    int temp = 0;
    temp = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    return (float)temp;
}

bool QComTools::WriteAsMsbData2File(const QString &file_path, const int point_num, float *data)
{
    unsigned char *msb_data = new unsigned char[point_num * sizeof(int)]{0};
    if(msb_data == nullptr)
        return false;
    QFile *data_file = CreateAndOpenDataFile(file_path);
    if(data_file == nullptr)
    {
        delete[] msb_data;
        return false;
    }
    for(int i = 0; i < point_num; i++)
    {
        CvtIntToMsb4Byte((int)(data[i]), msb_data + i * 4);
    }

    bool ok = WriteData2File(data_file, (char *)msb_data, point_num * sizeof(int));
    data_file->close();
    delete[] msb_data;
    delete data_file;
    return ok;
}

void QComTools::CvtIntToMsb4Byte(const int data, unsigned char *dest)
{
    dest[0] = (data >> 24) & 0xff;
    dest[1] = (data >> 16) & 0xFF;
    dest[2] = (data >> 8) & 0xFF;
    dest[3] = (data) & 0xFF;
}

void QComTools::Cvt3BDataToFloatMem(unsigned char *src, float *dest, const int point_num)
{
    for(int i = 0; i < point_num; i++)
    {
        dest[i] = CvtMsb3Byte2Float(src + i * 3);
    }
}

void QComTools::Cvt4BDataToFloatMem(unsigned char *src, float *dest, const int point_num)
{
    for(int i = 0; i < point_num; i++)
    {
        dest[i] = CvtMsb4Byte2Float(src + i * 4);
    }
}

bool QComTools::Read4BMsbDataToFlotMem(const QString file_path, float *dest, int total_point_num)
{
    int read_point_num = 0;
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Unbuffered))
    {
        qDebug()<<QString("read file path[%1] failed.").arg(file_path);
        return false;
    }
    // 修正点数
    if(total_point_num == 0)
    {
        read_point_num = file.size() / 4;
        if(file.size() != read_point_num * 4)
        {
            file.close();
            return false;
        }
    }else{
        read_point_num = total_point_num;
    }

    // 读取是否成功
    QByteArray data = file.read(read_point_num * 4);
    if(data.size() != read_point_num * 4)
    {
        file.close();
        return false;
    }
    // 根据修正后的数据读取
    //read_point_num = 8192;
    for(int i = 0; i < read_point_num; i++)
    {
        dest[i] = CvtMsb4Byte2Float((unsigned char *)(data.data() + i * 4));
    }
    file.close();
    return true;;
}

unsigned int QComTools::CvtMsb4Byte2UInt(const unsigned char *data)
{
    unsigned int temp = 0;
    temp = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    return temp;
}

unsigned int QComTools::CvtMsb3Byte2UInt(unsigned char *data)
{
    return  (0x00000000 | (*(data + 0) << 16) | (*(data + 1) << 8) | (*(data + 2)));
}
