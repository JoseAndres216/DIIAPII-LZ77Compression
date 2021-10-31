#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "LZ77Compression/LZ77Compression.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_compressButton_clicked()
{
    LZ77Compresion lz77;
    cout << lz77.LZ77(ui->inputTextEdit->toPlainText().toStdString(), 1) << endl;
    QString compressedText = QString::fromStdString(lz77.LZ77(ui->inputTextEdit->toPlainText().toStdString(), 1));
    ui->compressedOutputTextEdit->setText(compressedText);
}


void MainWindow::on_decompressButton_clicked()
{
    LZ77Compresion lz77;
    QString decompressedText = QString::fromStdString(lz77.LZ77(ui->inputTextEdit->toPlainText().toStdString(), 2));
    ui->decompressedOutputTextEdit->setText(decompressedText);
}

