#include <QApplication>
#include "QComTools.h"
#include "ReadSeismFile.h"
#include "qc_data_analysis.h"
#include <QApplication>
#include "QFileDialog"
#ifndef TEST_H
#define TEST_H
namespace test{
class test_noise{
public:
    void test_itrace_noise(QString filepath = "../Ins Noise20200803_171053962/qc_data_20200803_171101999.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
    void test_obc_noise(QString filepath = "../Ins Noise20200803_171053962/qc_data_20200803_171101999.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
    void test_obn_noise(QString filepath = "../Ins Noise20200803_171053962/qc_data_20200803_171101999.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
};

class test_bandwidth{
public:
    void test_itrace_bandwidth(QString filepath = "../Band Width20200803_171216864/qc_data_20200803_171224904.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
    void test_obc_bandwidth(QString filepath = "../Band Width20200803_171216864/qc_data_20200803_171224904.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
    void test_obn_bandwidth(QString filepath = "../Band Width20200803_171216864/qc_data_20200803_171224904.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
};

class test_capaitance{
public:
    void test_itrace_capaitance(QList<QString>filepath =
                            {"../Capaitance20200803_171136030/qc_data_20200803_171144070.dat",
                             "../Capaitance20200803_171136030/qc_data_20200803_171154088.dat",
                             "../Capaitance20200803_171136030/qc_data_20200803_171204110.dat",
                             "../Capaitance20200803_171136030/qc_data_20200803_171214129.dat"},
                            int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
//    void test_itrace_lowfreqbase(QString filepath = "../qc_data_20200803_171144070.dat", int ch_num = 72, int sp_rate = 1000, int sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
//    void test_itrace_lowfreqoutput(QString filepath = "../qc_data_20200803_171154088.dat", int ch_num = 72, int sp_rate = 1000, int sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
//    void test_itrace_highfreqbase(QString filepath = "../qc_data_20200803_171204110.dat", int ch_num = 72, int sp_rate = 1000, int sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
//    void test_itrace_highfreqout(QString filepath = "../qc_data_20200803_171214129.dat", int ch_num = 72, int sp_rate = 1000, int sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
    void test_obc_capaitance(QList<QString>filepath =
                            {"../Capaitance20200803_171136030/qc_data_20200803_171144070.dat",
                             "../Capaitance20200803_171136030/qc_data_20200803_171154088.dat",
                             "../Capaitance20200803_171136030/qc_data_20200803_171204110.dat",
                             "../Capaitance20200803_171136030/qc_data_20200803_171214129.dat"},
                            int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
    void test_obn_capaitance(QList<QString>filepath =
                            {"../Capaitance20200803_171136030/qc_data_20200803_171144070.dat",
                             "../Capaitance20200803_171136030/qc_data_20200803_171154088.dat",
                             "../Capaitance20200803_171136030/qc_data_20200803_171204110.dat",
                             "../Capaitance20200803_171136030/qc_data_20200803_171214129.dat"},
                            int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
};

class test_cmrr{
    void test_itrace_cmrr(QString filepath = "../Cmrr20200803_171104597/qc_data_20200803_171112634.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
    void test_obc_cmrr(QString filepath = "../Cmrr20200803_171104597/qc_data_20200803_171112634.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
    void test_obn_cmrr(QString filepath = "../Cmrr20200803_171104597/qc_data_20200803_171112634.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
};

class test_crosstalk{
    void test_itrace_crosstalk(QString filepath = "../Cross Talk20200803_171115296/qc_data_20200803_171112634.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
    void test_obc_crosstalk(QString filepath = "../Cross Talk20200803_171115296/qc_data_20200803_171112634.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
    void test_obn_crosstalk(QString filepath = "../Cross Talk20200803_171115296/qc_data_20200803_171112634.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
};

class test_gainerror{

};

class signal_to_noise_ration{

};

class test_phaseerror{
    void test_itrace_phaseerror(QString filepath = "../Phase Error20200803_171227548/qc_data_20200803_171235585.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
    void test_obc_phaseerror(QString filepath = "../Phase Error20200803_171227548/qc_data_20200803_171235585.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
    void test_obn_phaseerror(QString filepath = "../Phase Error20200803_171227548/qc_data_20200803_171235585.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);

};

class test_thd{
    void test_itrace_thd(QString filepath = "../Phase Error20200803_171227548/qc_data_20200803_171051342.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 2, float smpleintevms = 1.0);
    void test_obc_thd(QString filepath = "../Phase Error20200803_171227548/qc_data_20200803_171051342.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
    void test_obn_thd(QString filepath = "../Phase Error20200803_171227548/qc_data_20200803_171051342.dat", int ch_num = 72, int sp_rate = 1000, float sp_time = 4.096, int chanelnumofdevice = 10, float smpleintevms = 1.0);
};
}

#endif // TEST_H
