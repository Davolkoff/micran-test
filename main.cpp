#include <QCoreApplication>
#include <QtDebug>
#include <QTextStream>


//  интерфейс объявляет то, что должна уметь делать каждая операция
class NumericOperation
{
    public:
        virtual float calculate(float a, float b) = 0;
};

// класс сложения
class Addition : public NumericOperation
{
public:
    ~Addition() {};
    float calculate(float a, float b)
    {
        return a + b;
    }
};

// класс вычитания
class Substraction : public NumericOperation
{
public:
    ~Substraction() {};
    float calculate(float a, float b)
    {
        return a - b;
    }
};


// класс умножения
class Multiplication : public NumericOperation
{
public:
    ~Multiplication() {};
    float calculate(float a, float b)
    {
        return a * b;
    }
};


// класс деления
class Division : public NumericOperation
{
public:
    ~Division() {};
    float calculate(float a, float b)
    {
        if(b != 0)
        {
            return a / b;
        }
        else
        {
            qDebug() << "Zero division is impossible\n";
            return 0;
        }

    }
};


// фабрика, генерирующая операцию в зависимости от того, что ввел пользователь
class CalculatorFactory
{
    public:
        NumericOperation* createOperation(char sign)
        {
            if (sign == '+') return new Addition();
            else if (sign == '-') return new Substraction();
            else if (sign == '*') return new Multiplication();
            else if (sign == '/') return new Division();
            else return nullptr;
        }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream cin(stdin);
    QTextStream cout(stdout);

    while (true) {
        QString problem = cin.readLine();

        QString str_num1, str_num2;
        char problem_operator;
        for (int i = 0; i < problem.length(); ++i)
        {
            if (problem[i] == '+' || problem[i] == '-' || problem[i] == '*' || problem[i] == '/')
            {
                problem_operator = problem[i].toLatin1();
            }
            else if (problem[i].isDigit() || problem[i] == '.')
            {
                if (problem_operator == 0) str_num1 += problem[i];
                else str_num2 += problem[i];
            }
            else
            {
                cout << "Invalid input\n";
                return 0;
            }
        }

        if (str_num1.isEmpty() || str_num2.isEmpty())
        {
            cout << "Invalid input\n";
            return 0;
        }

        float num1 = str_num1.toFloat();
        float num2 = str_num1.toFloat();

        CalculatorFactory factory;
        NumericOperation* operation = factory.createOperation(problem_operator);
        if(operation == 0)
        {
            cout << "Invalid operator\n";
            return 0;
        }

        cout << operation->calculate(num1, num2) << "\n";
        delete operation;
    }
    return a.exec();
}
