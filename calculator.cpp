#include "calculator.h"
#include "ui_calculator.h"
#include <cmath>

#define PI 3.14159265

double calcValue = 0.0;
bool divTrigerred = false;
bool mulTrigerred = false;
bool addTrigerred = false;
bool subTrigerred = false;
bool sinTrigerred = false;
bool cosTrigerred = false;
bool tanTrigerred = false;
bool powerTrigerred = false;
bool factorialTrigerred = false;
bool logTrigerred = false;
bool lnTrigerred = false;
bool inverseTrigerred = false;
bool rootTrigerred = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcValue));

    QPushButton *numButtons[10];

    for(int i=0; i<10; ++i){
        QString butName = "Button_" + QString::number(i);

        numButtons[i] = Calculator::findChild<QPushButton *>(butName);

        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Decimal_Point, SIGNAL(released()), this, SLOT(DecimalPressed()));

    connect(ui->Addition, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Subtraction, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Multiplication, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Division, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualPressed()));

    connect(ui->Change_Sign, SIGNAL(released()), this, SLOT(ChangeSignPressed()));

    connect(ui->All_Clear, SIGNAL(released()), this, SLOT(AllClearPressed()));

    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearPressed()));

    connect(ui->Sin, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Cos, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Tan, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Logarithm, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Natural_Logarithm, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Power, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->Inverse, SIGNAL(released()), this, SLOT(InversePressed()));

    connect(ui->Factorial, SIGNAL(released()), this, SLOT(FactorialPressed()));

    connect(ui->SquareRoot, SIGNAL(released()), this, SLOT(OperatorPressed()));

    connect(ui->EulersNumber, SIGNAL(released()), this, SLOT(EulerPressed()));

}

double Calculator :: factorial(double num){

    if (num == 1 || num ==0){
        return 1;
    }
    else {
        return num * factorial(num-1);
    }

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator :: NumPressed(){

    QPushButton *button = (QPushButton *)sender();

    QString butVal = button->text();

    QString displayValue = ui->Display->text();

    if((displayValue.toDouble() == 0) || (displayValue.toDouble() == 0.0)){

        ui->Display->setText(butVal);

    }
    else{

        QString newVal = displayValue + butVal;

        double dblNewVal = newVal.toDouble();

        ui->Display->setText(QString::number(dblNewVal, 'g',16));

    }
}

void Calculator :: DecimalPressed(){

    static int countDec =0;

    QPushButton *button = (QPushButton *)sender();

    QString butVal = button->text();

    countDec++;

    QString displayValue = ui->Display->text();

    if(countDec==1){
        ui->Display->setText(displayValue+butVal);
    }
    else{
        ui->Display->setText(displayValue);
    }
}

void Calculator :: OperatorPressed(){

    divTrigerred = false;
    mulTrigerred = false;
    addTrigerred = false;
    subTrigerred = false;
    sinTrigerred = false;
    cosTrigerred = false;
    tanTrigerred = false;
    powerTrigerred = false;
    logTrigerred = false;
    lnTrigerred = false;
    rootTrigerred = false;

    QString displayValue = ui->Display->text();

    calcValue = displayValue.toDouble();

    QPushButton *button = (QPushButton *)sender();

    QString butVal = button->text();

    if(QString :: compare( butVal, "/", Qt :: CaseInsensitive)==0){

        divTrigerred=true;

    }
    else if(QString :: compare( butVal, "*", Qt :: CaseInsensitive)==0){

        mulTrigerred=true;

    }
    else if(QString :: compare( butVal, "+", Qt :: CaseInsensitive)==0){

        addTrigerred=true;

    }
    else if(QString :: compare( butVal, "-", Qt :: CaseInsensitive)==0){

        subTrigerred=true;

    }
    else if(QString :: compare( butVal, "sin", Qt :: CaseInsensitive)==0){

        sinTrigerred = true;

    }
    else if(QString :: compare( butVal, "cos", Qt :: CaseInsensitive)==0){

        cosTrigerred = true;

    }
    else if(QString :: compare( butVal, "tan", Qt :: CaseInsensitive)==0){

        tanTrigerred = true;

    }
    else if(QString :: compare( butVal, "log", Qt :: CaseInsensitive)==0){

        logTrigerred = true;

    }
    else if(QString :: compare( butVal, "ln", Qt :: CaseInsensitive)==0){

        lnTrigerred = true;

    }
    else if(QString :: compare( butVal, "X^Y", Qt :: CaseInsensitive)==0){

        powerTrigerred = true;

    }
    else if(QString :: compare( butVal, "√X", Qt :: CaseInsensitive)==0){

        rootTrigerred = true;

    }
    ui->Display->setText("");

}

void Calculator :: EqualPressed(){

    double solution = 0.0;

    int flag = 0;

    QString displayValue = ui->Display->text();

    double dblDisplayVal = displayValue.toDouble();

    if(divTrigerred || mulTrigerred || addTrigerred || subTrigerred){

        if(divTrigerred && (dblDisplayVal != 0 || dblDisplayVal != 0.0)){

            solution = calcValue / dblDisplayVal;

        }
        else if(divTrigerred && (dblDisplayVal == 0 || dblDisplayVal == 0.0)){

            flag = 1;

        }
        else if(mulTrigerred){

            solution = calcValue * dblDisplayVal;

        }
        else if(addTrigerred){

            solution = calcValue + dblDisplayVal;

        }
        else if(subTrigerred){

            solution = calcValue - dblDisplayVal;

        }
    }

    else if (sinTrigerred || cosTrigerred || tanTrigerred){

        if (sinTrigerred){
            solution = sin(dblDisplayVal * (PI/180));
        }

        else if(cosTrigerred){
            solution = cos(dblDisplayVal * (PI/180));
        }

        else{
            solution = tan(dblDisplayVal * (PI/180));
        }

    }

    else if (powerTrigerred){

        solution = pow(calcValue, dblDisplayVal);

    }

    else if (logTrigerred){

        solution = (log(dblDisplayVal)/log(10));

    }

    else if (lnTrigerred){

        solution = log(dblDisplayVal);

    }

    else if (rootTrigerred){

        solution = sqrt(dblDisplayVal);

    }

    if(flag == 1){

        ui->Display->setText("Division by zero ERROR");

    }
    else{
        ui->Display->setText(QString :: number(solution));
    }
}

void Calculator :: ChangeSignPressed(){

    QString displayVal = ui->Display->text();

    QRegExp reg("[-]?[0-9.]*");

    if(reg.exactMatch(displayVal)){

        double dblDisplayVal = displayVal.toDouble();

        double dblDisplayValSign = (-1) * dblDisplayVal;

        ui->Display->setText(QString :: number(dblDisplayValSign));

    }

}

void Calculator :: AllClearPressed(){

    ui->Display->setText("0");

}

void Calculator :: ClearPressed(){

    QString displayVal = ui->Display->text();

    if(displayVal.length() == 0 || displayVal.length() == 1 ){

        ui->Display->setText("0");

    }
    else{

        QString displayStr = displayVal.left(displayVal.length()-1);

        ui->Display->setText(displayStr);

    }
}

void Calculator :: FactorialPressed(){

    double solution = 0.0;

    int flag = 0;

    QString displayValue = ui->Display->text();

    double dblDisplayVal = displayValue.toDouble();

    if(dblDisplayVal < 0){
        flag = 1;
    }

    else{
        solution = factorial(dblDisplayVal);
    }

    if(flag == 1){

        ui->Display->setText("ERROR!");

    }
    else{
        ui->Display->setText(QString :: number(solution));
    }

}

void Calculator :: InversePressed(){

    double solution = 0.0;

    int flag = 0;

    QString displayValue = ui->Display->text();

    double dblDisplayVal = displayValue.toDouble();

    if (dblDisplayVal == 0){
        flag = 1;
    }

    else{
        solution = (1/dblDisplayVal);
    }
    if(flag == 1){

        ui->Display->setText("Division by zero ERROR");

    }
    else{
        ui->Display->setText(QString :: number(solution));
    }

}

void Calculator :: EulerPressed(){

    ui->Display->setText("2.71828183");

}
