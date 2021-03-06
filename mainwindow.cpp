#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<QString> fileName;
    QString name[4];
    name[0] = "/home/cty/workspace/OPENGL/OpenGL_Shader/opengl_shaderLesson07/build/Terrain.bmp";
    name[1] = "/home/cty/workspace/OPENGL/OpenGL_Shader/opengl_shaderLesson07/build/Detail.bmp";
    name[2] = "/home/cty/workspace/OPENGL/OpenGL_Shader/opengl_shaderLesson07_2/build/test1.jpg";
    name[3] = "/home/cty/workspace/OPENGL/OpenGL_Shader/opengl_shaderLesson07_2/build/test1n.jpg";

    for(int i=0;i<sizeof(name)/sizeof(name[0]);++i)
    {
        fileName.push_back(name[i]);
    }

    ui->widget->init_QGW(fileName);

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
    timer->start(20);

    ui->widget->parent = this;
    this->installEventFilter(ui->widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimeOut()
{
    ui->widget->drawImage();
}
