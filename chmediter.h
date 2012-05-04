#ifndef CHMEDITER_H
#define CHMEDITER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QDebug>

namespace Ui {
class chmEditer;
}

class chmEditer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit chmEditer(QWidget *parent = 0);
    ~chmEditer();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::chmEditer *ui;
};

#endif // CHMEDITER_H
