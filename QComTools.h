#ifndef QCOMTOOLS_H
#define QCOMTOOLS_H
#include <QString>
#include <QStringList>
#include <QList>
#include <QByteArray>
#include <QRegExp>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QThread>

namespace QComTools {
// 字符串转换，不检查参数是否正确
int CvtMsb3Byte2Int(const unsigned char *data);
float CvtMsb3Byte2Float(const unsigned char *data);
float CvtMsb4Byte2Float(const unsigned char *data);
unsigned int CvtMsb4Byte2UInt(const unsigned char *data);
void CvtIntToMsb4Byte(const int data, unsigned char *dest);
unsigned int CvtMsb3Byte2UInt(unsigned char *data);

// 默认MSB
void CvtMsbHexData2Float(const unsigned char *sour, float *dest,  const unsigned int sp_num);
void CvtFloat2MsbHexData(const float *sour, unsigned char *dest,  const unsigned int sp_num);
void CvtMsbHexData2Int(const unsigned char *sour, int *dest,  const unsigned int sp_num);
void CvtInt2MsbHexData(const int *sour, unsigned char *dest,  const unsigned int sp_num);

// 仅支持内置数据类型
template <class T>
QString QList2String(const QList<T> &data)
{
    QString str;
    for(auto it = data.constBegin(); it != data.constEnd(); it++)
    {
        str += QString("%1 ").arg(*it);
    }
    return str;
}

QString Hex2Str(const unsigned char *data, const int len);

// 只支持空格或者','分割的字符串
QByteArray HexStr2HexStr(const QString &str, bool *ok = nullptr);
QString HexData2HexStr(const unsigned char *data, const int len,
                                const bool with_space_splite = false);

// 时间标记
enum class DateTimeTagFormat{
    FullWithUnderLineSplite,    // yyyyMMdd_hhmmsszzz
    NormalFull,      // yyyy/MM/dd hh:mm:ss.zzz
    NormalDateOnly,    // yyyy/MM/dd
    NormalTimeOnly, // hh:mm:ss
    NormalTimeMin,  // mm:ss
    NormalTimeWithMinSec // hh:mm:ss.zzz
};
QString CurrDateTimeTag(DateTimeTagFormat type = DateTimeTagFormat::FullWithUnderLineSplite);

// 文件读写
bool WriteData2File(QFile *file, const char *data, const int len);
bool WriteData2File(QFile *file, const QString &data);
int ReadSeismDataFromFile(const QString &file_path, const int sp_rate, const double sp_time, float *data);
bool WriteAsMsbData2File(const QString &file_path, const int point_num, float *data);
void Cvt3BDataToFloatMem(unsigned char *src, float *dest, const int point_num);
void Cvt4BDataToFloatMem(unsigned char *src, float *dest, const int point_num);
bool Read4BMsbDataToFlotMem(const QString file_path, float *dest, int total_point_num = 0);

QFile* CreateAndOpenTextFile(const QString &file_path);
QFile* CreateAndOpenDataFile(const QString &file_path);

void ReleaseFile(QFile *&file);

bool PathStrIsAbsPath(const QString &path);
bool CreateDir(const QString &dir_path);
bool ReCreateDir(const QString &dir_path);
bool DelDir(const QString &dir_path);

// 正则表达式
QRegExp IpRegExp();

qintptr GetObjPtrValue(const void *obj);

void MoveObjectToThreadListAndStart(QObject *object, QMap<qintptr, QThread *> &thread_list);
void MoveOutObjectFromThreadList(const QObject *object, QMap<qintptr, QThread *> &thread_list);
}

#endif // QCOMTOOLS_H
