#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include "QPixmap"
#include "QLabel"
#include "QDebug"
#include "QFileInfo"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_amban_xam_clicked()
{
    QImage image_in(ui->ln_filename->text());
    QImage image_out(image_in.width(), image_in.height(),QImage::Format_ARGB32);
    for (int i = 0; i < image_in.width(); i++)
        {
            for (int j = 0; j < image_in.height(); j++)
            {
                QRgb rgb = image_in.pixel(i, j);
                int gray = qGray(rgb);
                QRgb color_in = qRgb(gray, gray, gray);
                int out = 255 - gray;
                if (out > 255) out = 255;
                else if (out < 0) out = 0;
                QRgb color_out = qRgb(out, out, out);
                image_out.setPixel(i, j, color_out);
            }
        }
        QLabel* label_in = new QLabel();
        label_in->setPixmap(QPixmap::fromImage(image_in));
        label_in->show();

        QLabel* label_out = new QLabel();
        label_out->setPixmap(QPixmap::fromImage(image_out));
        label_out->show();
}


void MainWindow::on_bt_Chon_clicked()
{
   // QString filename = QFileDialog::getOpenFileName(this, "Open File","C:/CVIPtools/images","*. * ALL Files;*.bmp;*.jpeg;*.ppm;*.png;*.jpg");
     QString filename = QFileDialog::getOpenFileName(this, "Open File","C:/Users/DELL/OneDrive/Pictures/Screenshots");
        if (filename.isEmpty())
            return;

        ui->ln_filename->setText(filename);

        QPixmap pixmap(filename);
        QLabel *label = new QLabel();
        label->setPixmap(pixmap);
        label->setWindowTitle(QFileInfo(filename).fileName());
        label->show();
}

void MainWindow::on_btn_amban_mau_clicked()
{
    QImage image_in(ui->ln_filename->text());
    QImage image_out(image_in.width(), image_in.height(),QImage::Format_ARGB32);
        for (int i = 0; i < image_in.width(); i++)
        {
            for (int j = 0; j < image_in.height(); j++)
            {
                QRgb rgb = image_in.pixel(i, j);
                QColor color(rgb);
                int red = color.red();
                int green = color.green();
                int blue = color.blue();
                int n_red = 255 - red;
                int n_green = 255 - green;
                int n_blue = 255 - blue;
                QRgb color_out = qRgb(n_red, n_green, n_blue);
                image_out.setPixel(i, j, color_out);
            }
        }
        QLabel* label_in = new QLabel();
        label_in->setPixmap(QPixmap::fromImage(image_in));
        label_in->show();

        QLabel* label_out = new QLabel();
        label_out->setPixmap(QPixmap::fromImage(image_out));
        label_out->show();
}

void MainWindow::on_btn_phannguong_clicked()
{
    QImage image_in(ui->ln_filename->text());
    QImage image_out(image_in.width(), image_in.height(), QImage::Format_RGB32);

    int c = ui->ln_phannguong->text().toInt();
    for (int i = 0; i < image_in.width(); i++)
    {
        for (int j = 0; j < image_in.height(); j++)
        {
            QRgb rgb = image_in.pixel(i, j);
            int gray = qGray(rgb);
            QRgb color_in = qRgb(gray, gray, gray);
            image_in.setPixel(i, j, color_in);
            int out = gray;
            if (out > c) out = 255;
            else if (out < c) out = 0;
            QRgb color_out = qRgb(out, out, out);
            image_out.setPixel(i, j, color_out);
        }
    }

    QLabel* label_in = new QLabel();
    label_in->setPixmap(QPixmap::fromImage(image_in));
    label_in->show();

    QLabel* label_out = new QLabel();
    label_out->setPixmap(QPixmap::fromImage(image_out));
    label_out->show();
}

// Hàm Histogram_GrayImage
void MainWindow::Histogram_GrayImage(const QImage &img, const int &his_height)
{
    int h[256];
        for (int i = 0; i < 256; i++)
        {
            h[i] = 0;
        }

        QImage image_in(img);
        for (int x = 0; x < img.width(); x++)
        {
            for (int y = 0; y < img.height(); y++)
            {
                QRgb color = image_in.pixel(x, y);
                int gray = qGray(color);
                QRgb color_in = qRgb(gray, gray, gray);
                image_in.setPixel(x, y, color_in);
                h[gray]++;
            }
        }

        int max = 0;
        for (int i = 0; i < 256; i++)
        {
            if (h[i] > max)
                max = h[i];
        }

        QImage img_his = QImage(256, his_height, QImage::Format_RGB888);
        img_his.fill(Qt::white);

        int lineHeight;
        for (int i = 0; i < 256; i++)
        {
            lineHeight = his_height * h[i] / max;
            for (int j = his_height; j >= his_height - lineHeight; j--)
            {
                img_his.setPixel(i, j, qRgb(0, 0, 0));
            }
        }

        //QImage image_out(img.width(), img.height(), QImage::Format_RGB888);
        QLabel* label_in = new QLabel();
        label_in->setPixmap(QPixmap::fromImage(image_in));
        label_in->show();

        QLabel* label_out = new QLabel();
        label_out->setPixmap(QPixmap::fromImage(img_his));
        label_out->show();
}

void MainWindow::on_btn_histogram_xam_clicked()
{
    QImage img(ui->ln_filename->text());
    Histogram_GrayImage(img, 200); // Chiều cao histogram là 200
}

void MainWindow::Histogram_ColorImage(const QImage &img, const int &his_height)
{
    int hr[256];
    int hg[256];
    int hb[256];
    for (int i = 0; i < 256; i++)
    {
        hr[i] = 0;
        hg[i] = 0;
        hb[i] = 0;
    }

    QImage image_in(img);
    for (int x = 0; x < img.width(); x++)
    {
        for (int y = 0; y < img.height(); y++)
        {
            QRgb color = img.pixel(x, y);
            int green = qGreen(color);
            int red = qRed(color);
            int blue = qBlue(color);
            hr[red]++;
            hg[green]++;
            hb[blue]++;
        }
    }

    int maxr = 0, maxg = 0, maxb = 0;
    for (int i = 0; i < 256; i++)
    {
        if (hr[i] > maxr) maxr = hr[i];
        if (hg[i] > maxg) maxg = hg[i];
        if (hb[i] > maxb) maxb = hb[i];
    }

    QImage img_histr = QImage(256, his_height, QImage::Format_RGB32);
    img_histr.fill(Qt::white);

    for (int i = 0; i < 256; i++)
    {
        int lineHeight = (maxr > 0) ? (hr[i] * his_height / maxr) : 0;
        for (int j = his_height; j > his_height - lineHeight; j--)
        {
            img_histr.setPixel(i, j, qRgb(255, 0, 0));
        }
    }

    QImage img_histg = QImage(256, his_height, QImage::Format_RGB32);
    img_histg.fill(Qt::white);

    for (int i = 0; i < 256; i++)
    {
        int lineHeight = (maxg > 0) ? (hg[i] * his_height / maxg) : 0;
        for (int j = his_height; j > his_height - lineHeight; j--)
        {
            img_histg.setPixel(i, j, qRgb(0, 255, 0));
        }
    }

    QImage img_histb = QImage(256, his_height, QImage::Format_RGB32);
    img_histb.fill(Qt::white);

    for (int i = 0; i < 256; i++)
    {
        int lineHeight = (maxb > 0) ? (hb[i] * his_height / maxb) : 0;
        for (int j = his_height; j > his_height - lineHeight; j--)
        {
            img_histb.setPixel(i, j, qRgb(0, 0, 255));
        }
    }

    QLabel* label_red = new QLabel();
    label_red->setPixmap(QPixmap::fromImage(img_histr));
    label_red->show();

    QLabel* label_green = new QLabel();
    label_green->setPixmap(QPixmap::fromImage(img_histg));
    label_green->show();

    QLabel* label_blue = new QLabel();
    label_blue->setPixmap(QPixmap::fromImage(img_histb));
    label_blue->show();
}

void MainWindow::on_btn_histogram_mau_clicked()
{
    QImage img(ui->ln_filename->text());
    Histogram_ColorImage(img, 200); // Chiều cao histogram là 200
}

void MainWindow::on_btn_dotuongphan_xam_clicked()
{
    QImage image_in(ui->ln_filename->text());
        QImage image_out(image_in.width(), image_in.height(), QImage::Format_RGB32);

        float c = ui->ln_dotuongphan->text().toFloat();

        for(int i = 0; i < image_in.width(); i++)
        {
            for(int j = 0; j < image_in.height(); j++)
            {
                QRgb rgb = image_in.pixel(i, j);
                int gray = qGray(rgb);
                QRgb color_in = qRgb(gray, gray, gray);
                image_in.setPixel(i, j, color_in);

                int out = gray * c;
                if(out > 255) out = 255;
                else if(out < 0) out = 0;

                QRgb color_out = qRgb(out, out, out);
                image_out.setPixel(i, j, color_out);
            }
        }

        QLabel* label_in = new QLabel();
        label_in->setPixmap(QPixmap::fromImage(image_in.scaled(640, 480)));
        label_in->show();

        QLabel* label_out = new QLabel();
        label_out->setPixmap(QPixmap::fromImage(image_out.scaled(640, 480)));
        label_out->show();
}

void MainWindow::on_btn_dotuongphan_mau_clicked()
{
    QImage image_in(ui->ln_filename->text());
        QImage image_out(image_in.width(), image_in.height(), QImage::Format_RGB32);

        float c = ui->ln_dotuongphan->text().toFloat();

        for(int i = 0; i < image_in.width(); i++)
        {
            for(int j = 0; j < image_in.height(); j++)
            {
                QRgb rgb = image_in.pixel(i, j);

                // Lấy giá trị từng kênh màu
                int red = qRed(rgb);
                int green = qGreen(rgb);
                int blue = qBlue(rgb);

                // Nhân hệ số tương phản c
                int r_out = red * c;
                int g_out = green * c;
                int b_out = blue * c;

                // Giới hạn giá trị từ 0 đến 255
                r_out = qBound(0, r_out, 255);
                g_out = qBound(0, g_out, 255);
                b_out = qBound(0, b_out, 255);

                // Tạo pixel mới sau xử lý
                QRgb color_out = qRgb(r_out, g_out, b_out);
                image_out.setPixel(i, j, color_out);
            }
        }

        QLabel* label_in = new QLabel();
        label_in->setPixmap(QPixmap::fromImage(image_in.scaled(640, 480)));
        label_in->show();

        QLabel* label_out = new QLabel();
        label_out->setPixmap(QPixmap::fromImage(image_out.scaled(640, 480)));
        label_out->show();
}

void MainWindow::on_btn_biendoituyentinh_histogram_clicked()
{
    QImage image_in(ui->ln_filename->text());
        QImage image_out(image_in.width(), image_in.height(), QImage::Format_RGB32);

        int min_gray = 255;
        int max_gray = 0;

        // Tìm min và max gray
        for (int i = 0; i < image_in.width(); i++)
        {
            for (int j = 0; j < image_in.height(); j++)
            {
                QRgb rgb = image_in.pixel(i, j);
                int gray = qGray(rgb);

                if (gray < min_gray) min_gray = gray;
                if (gray > max_gray) max_gray = gray;
            }
        }

        // Áp dụng biến đổi tuyến tính
        for (int i = 0; i < image_in.width(); i++)
        {
            for (int j = 0; j < image_in.height(); j++)
            {
                QRgb rgb = image_in.pixel(i, j);
                int gray = qGray(rgb);

                int out = (gray - min_gray) * 255 / (max_gray - min_gray);
                out = qBound(0, out, 255); // đảm bảo hợp lệ

                QRgb color_out = qRgb(out, out, out);
                image_out.setPixel(i, j, color_out);
            }
        }

        // Hiển thị ảnh gốc và ảnh đã xử lý
        QLabel* label_in = new QLabel();
        label_in->setPixmap(QPixmap::fromImage(image_in.scaled(640, 480)));
        label_in->show();

        QLabel* label_out = new QLabel();
        label_out->setPixmap(QPixmap::fromImage(image_out.scaled(640, 480)));
        label_out->show();
}
// CÂN BẰNG HISTOGRAM
void MainWindow::on_btn_canbang_histogram_clicked()
{
    QImage image_in(ui->ln_filename->text());
        QImage image_out(image_in.width(), image_in.height(), QImage::Format_RGB32);

        int histogram[256] = {0};
        int width = image_in.width();
        int height = image_in.height();

        // 1. Tính histogram
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                QRgb rgb = image_in.pixel(i, j);
                int gray = qGray(rgb);
                histogram[gray]++;
            }
        }

        // 2. Tính hàm phân phối tích lũy (CDF)
        int cdf[256] = {0};
        cdf[0] = histogram[0];
        for (int i = 1; i < 256; i++)
        {
            cdf[i] = cdf[i - 1] + histogram[i];
        }

        // 3. Tính giá trị xám mới cho mỗi mức
        int totalPixels = width * height;
        int lut[256]; // Look-Up Table
        for (int i = 0; i < 256; i++)
        {
            lut[i] = qBound(0, (cdf[i] * 255) / totalPixels, 255);
        }

        // 4. Tạo ảnh mới từ LUT
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                int gray = qGray(image_in.pixel(i, j));
                int new_gray = lut[gray];
                QRgb color_out = qRgb(new_gray, new_gray, new_gray);
                image_out.setPixel(i, j, color_out);
            }
        }

        // 5. Hiển thị ảnh
        QLabel* label_in = new QLabel();
        label_in->setPixmap(QPixmap::fromImage(image_in.scaled(640, 480)));
        label_in->show();

        QLabel* label_out = new QLabel();
        label_out->setPixmap(QPixmap::fromImage(image_out.scaled(640, 480)));
        label_out->show();
}

// LỌC TRUNG BÌNH
void MainWindow::on_btn_loctrungbinh_clicked()
{
        QImage image_in(ui->ln_filename->text());
        // khai bao cho mat na chap 3x3
        int size = ui->ln_kickthuocmatna->text().toInt();
        int margin = (size - 1)/2;
        int cells = size * size;

        QImage image_out(image_in.width() - margin, image_in.height() - margin, QImage::Format_RGB32);
        int sumR, sumG, sumB;

        QColor color;
        for (int x = margin; x < image_in.width() - margin; x++)
        {
            for (int y = margin; y < image_in.height() - margin; y++)
            {
                sumR = sumG = sumB = 0;
                for (int i = -margin; i <= margin; i++)
                {
                    for (int j = -margin; j <= margin; j++)
                    {
                        color = image_in.pixel(x+i, y+j);
                        sumR += color.red();
                        sumG += color.green();
                        sumB += color.blue();
                    }
                }
                image_out.setPixel(x, y, qRgb(sumR/cells, sumG/cells, sumB/cells));
            }
        }

        QLabel * label_in = new QLabel();
        label_in->setPixmap(QPixmap::fromImage(image_in.scaled(1024, 768)));
        label_in->setToolTip("Hinh Goc");
        label_in->show();

        QLabel * label = new QLabel();
        label->setPixmap(QPixmap::fromImage(image_out.scaled(1024, 768)));
        label->setToolTip("Hinh da xu ly");
        label->show();

        QString fname = QFileDialog::getSaveFileName();
        image_out.save(fname);
}

// LỌC TRUNG VỊ
void MainWindow::on_btn_loctrungvi_clicked()
{
    QImage image_in(ui->ln_filename->text());
        // khai bao cho mat na chap
        int size = ui->ln_kickthuocmatna->text().toInt();
        int margin = (size - 1)/2;
        int cells = size*size;

        QImage image_out(image_in.width() - margin, image_in.height() - margin, QImage::Format_RGB32);

        for (int x = margin; x < image_in.width() - margin; x++)
        {
            for (int y = margin; y < image_in.height() - margin; y++)
            {
                int k = 0;
                int h[cells];
                for (int i = -margin; i <= margin; i++)
                {
                    for (int j = -margin; j <= margin; j++)
                    {
                        QRgb color = image_in.pixel(x+i, y+j);
                        int gray = qGray(color);
                        h[k] = gray;
                        k++;
                    }
                }
                qSort(h, h + cells);
                int meanV = h[cells - 1]/2;
                image_out.setPixel(x, y, qRgb(meanV, meanV, meanV));
            }
        }
}

int MainWindow::Random(int n)
{
    return rand() % n;
}

QImage MainWindow::imNoise_Gray(QImage &image_in, float level)
{
    QImage image_out = image_in;

    int noisePoint = image_in.width() * image_in.height() * level;
    for (int i = 0; i < noisePoint; i++)
    {
        int x = Random(image_in.width());
        int y = Random(image_in.height());
        int a = Random(2);
        if (a == 0)
            image_out.setPixel(x, y, qRgb(0, 0, 0));
        else
            image_out.setPixel(x, y, qRgb(255, 255, 255));
    }
    return image_out;
}
void MainWindow::on_btn_nhieumuoitieu_clicked()
{
    QImage image_in(ui->ln_filename->text());
        QImage image_inGray(image_in.width(), image_in.height(), QImage::Format_RGB32);

        for(int i = 0; i < image_in.width(); i++)
        {
            for(int j = 0; j < image_in.height(); j++)
            {
                QRgb rgb = image_in.pixel(i,j);
                int gray = qGray(rgb);
                QRgb color_in = qRgb(gray, gray, gray);
                image_inGray.setPixel(i,j, color_in);
            }
        }

        float percentage = (ui->ln_tylenhieu->text().toInt())/100;

        QImage image_out = imNoise_Gray(image_inGray, percentage);

        QLabel * label_in = new QLabel();
        label_in->setPixmap(QPixmap::fromImage(image_inGray.scaled(1024, 768)));
        label_in->setToolTip("Hinh Goc");
        label_in->show();

        QLabel * label = new QLabel();
        label->setPixmap(QPixmap::fromImage(image_out.scaled(1024, 768)));
        label->setToolTip("Hinh da xu ly");
        label->show();

        QString fname = QFileDialog::getSaveFileName();
        image_out.save(fname);
}

void MainWindow::on_btn_loc_gradient_clicked()
{
    QImage image_in(ui->ln_filename->text ());
        QImage image_out_Gx(image_in.width()-1,image_in.height(),QImage::Format_ RGB32);
        QImage image_out_Gy(image_in.width(),image_in.height()-1,QImage::Format_ RGB32);
        for (int i = 0; i < image_in.width () - 1; i++)
        {
            for (int j = 0; j < image_in.height (); j++)
            {
                QRgb color1 = image_in.pixel (i, j);
                int grayl = qGray (color1);
                QRgb color2 = image_in.pixel (i, j);
                int gray2 = qGray (color2);
                int newgray = abs (gray2 - gray1);
                image_out_Gx.setPixel (1, j, qRgb (newgray, newgray, newgray));
            }
        }
        for (int i = 0; i < image_in.width(); i++)
        {
            for (int j = 0; j < image_in.height ()-1; j++)
            {
                QRgb color1 = image_in.pixel (i, j);
                int grayl = qGray (color1);
                QRgb color2 = image_in.pixel (i, j);
                int gray2 = qGray (color2);
                int newgray = abs (gray2 - gray1);
                image_out_Gy.setPixel (i, j, qRgb (newgray, newgray, newgray));
            }
        }
        QRgb color1 = image_in.pixel (i, j);
        int grayl = qGray (color1);
        QRgb color2 = image_in.pixel (i, j+1);
        int gray2 = qGray (color2);
        int newgray = abs (gray2 - gray1);
        image_out_Gy.setPixel (i, j, qRgb (newgray, newgray, newgray));
    }
    QLabel* label_in = new QLabel ();
    label_in->setPixmap (QPixmap::fromImage(image_in.scaled (1024,760)));
    label_in->show ();
    QLabel *label_Gx = new QLabel ();
    label_Gx->setPixmap (QPixmap::fromImage(image_out_Gx.scaled (1024,760)));
    label_Gx->show ();
    QLabel *label_Gy = new QLabel ();
    label_Gy->setPixmap (QPixmap::fromImage (image_out_Gy.scaled (1024,760)));
    label_Gy->show ();
}

void MainWindow::on_btn_loc_laplace_clicked()
{

}
