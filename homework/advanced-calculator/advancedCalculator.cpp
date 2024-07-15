#include <map>
#include <string>
#include <type_traits>
#include <cmath>
#include <functional>

enum class ErrorCode
{
    Ok,
    BadCharacter, // znak inny niż liczba
    BadFormat, // zły format komendy np. + 5 4, powinno być 4 + 5
    DivideBy0, // dzielenie przez 0
    SqrtOfNegativeNumber, // pierwiastek z liczby ujemnej
    ModuleOfNonIntegerValue // próba obliczenia % na liczbie niecałkowitej
};

bool is_operation(char a)
{
    if(a == '+' || a == '-' || a == '*' || a == '/' || a == '!' || a == '^' || a == '$' || a == '%')
    {
        return true;
    }
    else return false;
}

bool is_integer(double &a)
{
    if(a - std::floor(a) != 0)
    {
        return false;
    }
    else return true;
}

char seperate(std::string input, double &first, double &second)
{
    char operation = 'n';
    int kr1 = 0, kr2 = 0, comma = 0; // ile jest kropek w liczbie, ile jest przecinkow
    bool k = false, m = false; // czy op jest na 2 msc, czy op zost pobrana
    std::string f = "", s = "";
    for(long unsigned i = 0; i < input.size(); ++i)
    {
        if(isspace(input[i]))
        {
            if(f.size() > 0 && !k)
            {
                k = !k;
            }
            continue;
        }
        if(input[i] == ',')
        {
            ++comma;
            continue;
        }
        if(isdigit(input[i]) || input[i] == '.' || (input[i] == '-' && isdigit(input[i + 1]) && !isdigit(input[i - 1])))
        {
            if(!k)
            {
                if(input[i] == '.')
                {
                    ++kr1;
                }
                f += input[i];
                continue;
            }
            else 
            {
                if(input[i] == '.')
                {
                    ++kr2;
                }
                s += input[i];
                continue;
            }
        }
        if(is_operation(input[i]))
        {
            if(f.size() > 0 && !k)
            {
                k = !k;
            }
            if(f.size() == 0 && !k)
            {
                operation = '0';
                break;
            }
            if(!m)
            {
                operation = input[i];
                m = !m;
            }
            else
            {
                return '0';
                break;
            }
        }
        else
        {
            return 'a';
            break;
        }
    }
    if(f.size() != 0)
    {
        first = std::stod(f);
    }
    if(s.size() != 0)
    {
        second = std::stod(s);
    }
    if(comma != 0)
    {
        return '0';
    }
    if(operation != '!' && (f == "" || s == ""))
    {
        return '0';
    }
    if(second < 0 && operation == 'n')
    {
        operation = '-';
        second = std::abs(second);
    }
    else if(operation == 'n')
    {
        return '0';
    }
    if(kr1 > 1 || kr2 > 1)
    {
        return '0';
    }
    return operation;
}

ErrorCode process(std::string input, double* out)
{
    std::map<char, std::function<double(double&, double&)>> map{
        {'+', [](double &a, double &b){ return a + b; }},
        {'*', [](double &a, double &b){ return a * b; }},
        {'-', [](double &a, double &b){ return a - b; }},
        {'/', [](double &a, double &b){ return a / b; }},
        {'%', [](double &a, double &b){ return std::fmod(a, b); }},
        {'^', [](double &a, double &b){ return std::pow(a, b); }},
        {'$', [](double &a, double &b){ return std::pow(a, 1 / b); }},
        {'!', [](double &a, double &b){ return std::tgamma(a + 1); }}
    };
    double first = 0, second = 0;
    char operation = seperate(input, first, second);
    switch (operation)
    {
        case 'a':
        {
            return ErrorCode::BadCharacter;
            break;
        }
        case '0':
        {
            return ErrorCode::BadFormat;
            break;
        }
        case '+':
        {
            *out = map['+'](first, second);
            return ErrorCode::Ok;
            break;
        }
        case '-':
        {
            *out = map['-'](first, second);
            return ErrorCode::Ok;
            break;
        }
        case '*':
        {
            *out = map['*'](first, second);
            return ErrorCode::Ok;
            break;
        }
        case '/':
        {
            if(second == 0)
            {
                return ErrorCode::DivideBy0;
                break;
            }
            else
            {
                *out = map['/'](first, second);
                return ErrorCode::Ok;
                break;
            }
        }
        case '%':
        {
            if(!is_integer(first) || !is_integer(second))
            {
                return ErrorCode::ModuleOfNonIntegerValue;
                break;
            }
            else
            {
                *out = map['%'](first, second);
                return ErrorCode::Ok;
                break;
            }
        }
        case '^':
        {
            *out = map['^'](first, second);
            return ErrorCode::Ok;
            break;
        }
        case '$':
        {
            if(first < 0)
            {
                return ErrorCode::SqrtOfNegativeNumber;
                break;
            }
            else
            {
                *out = map['$'](first, second);
                return ErrorCode::Ok;
                break;
            }
        }
        case '!':
        {
            if(first != 0 && second != 0)
            {
                return ErrorCode::BadFormat;
                break;
            }
            else
            {
                if(first < 0)
                {
                    *out = -map['!'](first, second);
                    return ErrorCode::Ok;
                    break;
                }
                else
                {
                    *out = map['!'](first, second);
                    return ErrorCode::Ok;
                    break;
                }
            }
        }
        default:
            return ErrorCode::BadCharacter;
            break;
    }
}
