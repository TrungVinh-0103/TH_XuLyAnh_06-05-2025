#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Khai báo hàm Histogram_GrayImage
    void Histogram_GrayImage(const QImage &img, const int &his_height);

    void Histogram_ColorImage(const QImage &img, const int &his_height);

    int Random(int n);

    QImage imNoise_Gray(QImage &image_in, float level);
private slots:


    void on_btn_amban_xam_clicked();

    void on_bt_Chon_clicked();

    void on_btn_amban_mau_clicked();

    void on_btn_phannguong_clicked();

    void on_btn_histogram_xam_clicked();

    void on_btn_histogram_mau_clicked();

    void on_btn_dotuongphan_xam_clicked();

    void on_btn_dotuongphan_mau_clicked();

    void on_btn_biendoituyentinh_histogram_clicked();

    void on_btn_canbang_histogram_clicked();

    void on_btn_loctrungbinh_clicked();

    void on_btn_loctrungvi_clicked();

    void on_btn_nhieumuoitieu_clicked();

    void on_btn_loc_gradient_clicked();

private:
    Ui::MainWindow *ui;
    QScrollArea *scrollArea; // Khai báo biến scrollArea
    QImage image_in;  // Biến để lưu ảnh đầu vào
    QImage image_out; // Biến để lưu ảnh đầu ra
    QImage image_out_Gx;
    QImage image_out_Gy;
};

#endif // MAINWINDOW_H
