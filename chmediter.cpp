#include "chmediter.h"
#include "ui_chmediter.h"

chmEditer::chmEditer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chmEditer)
{
    ui->setupUi(this);
    on_pushButton_clicked();
}

chmEditer::~chmEditer()
{
    delete ui;
}

class chmHeader
{
public:
    QString header;
    quint32 version;
    quint32 lenght;
    quint32 timestamp;
    quint32 languageID;
    QByteArray GUID1;
    QByteArray GUID2;

};

void chmEditer::on_pushButton_clicked()
{
    //
    chmHeader hd;
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Открыть chm"), ".", tr("Chm Files (*.chm)"));
//    fileName = "D:\\ferz\\chm1\\TestPrj.chm";
    QFile f;
    f.setFileName(fileName);
    if (f.open(QIODevice::ReadOnly))
    {
        QDataStream stream;
        stream.setDevice(&f);
        stream.setByteOrder(QDataStream::LittleEndian);

        char *tmp1;
        tmp1 = new char[4];
        stream.readRawData(tmp1,4);
        hd.header = tmp1;
        delete tmp1;

        stream>> hd.version;
        stream>> hd.lenght;
        stream.skipRawData(4);
        stream>>hd.timestamp;
        stream>>hd.languageID;

        tmp1 = new char[10];
        stream.readRawData(tmp1,10);
        hd.GUID1 = tmp1;
        delete tmp1;
        tmp1 = new char[10];
        stream.readRawData(tmp1,10);
        hd.GUID2 = tmp1;
        delete tmp1;

        qDebug()<<hd.GUID1;
        ui->textEdit->append("<b>Заголовок</b>: "+hd.header);
        ui->textEdit->append("<b>Версия</b>: "+QString("%1").arg(hd.version));
        ui->textEdit->append("<b>полный размер заголовка</b> : "+QString("%1").arg(hd.lenght));
        ui->textEdit->append("<b>Язык</b> : "+QString("%1").arg(hd.languageID,0, 16));
    }
    else
    {qDebug()<<"файл не открыт";}

}
