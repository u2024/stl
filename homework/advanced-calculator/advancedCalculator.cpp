#include <map>
#include <string>
#include <type_traits>
#include <cmath>
#include <functional>

enum class ErrorCode
{
    OK,
    BadCharacter, // znak inny niż liczba
    BadFormat, // zły format komendy np. + 5 4, powinno być 4 + 5
    DivideBy0, // dzielenie przez 0
    SqrtOfNegativeNumber, // pierwiastek z liczby ujemnej
    ModuleOfNonIntegerValue // próba obliczenia % na liczbie niecałkowitej
};

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
    bool k = false, m = false; char operation = '0';
    std::string f = "", s = "";
    for(long unsigned i = 0; i < input.size(); ++i)
    {
        if(isspace(input[i]))
        {
            continue;
        }
        else if(isdigit(input[i]) || input[i] == '.' || input[i] == '-' && isdigit(input[i + 1]))
        {
            if(!k)
            {
                f += input[i];
                continue;
            }
            else 
            {
                s += input[i];
                continue;
            }
        }
        if(ispunct(input[i]) && input[i] != '.')
        {
            k = !k;
            if(!m)
            {
                operation = input[i];
                m = !m;
            }
            else operation = '0';
        }
        else if(isalpha(input[i]))
        {
            operation = 'a';
            break;
        }
    }
    if(f.size() != 0 && s.size() != 0)
    {
        first = std::stod(f);
        second = std::stod(s);
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
        {'!', [](double &a, double &b){ return std::tgamma(a); }}
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
            return ErrorCode::OK;
            break;
        }
        case '-':
        {
            *out = map['-'](first, second);
            return ErrorCode::OK;
            break;
        }
        case '*':
        {
            *out = map['*'](first, second);
            return ErrorCode::OK;
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
                return ErrorCode::OK;
                break;
            }
        }
        case '%':
        {
            if(!is_integer(first) || !is_integer(second))
            {
                return ErrorCode::ModuleOfNonIntegerValue;
            }
            else
            {
                *out = map['%'](first, second);
                return ErrorCode::OK;
                break;
            }
        }
        case '^':
        {
            *out = map['^'](first, second);
            return ErrorCode::OK;
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
                return ErrorCode::OK;
                break;
            }
        }
        case '!':
        {
            *out = map['!'](first, second);
            return ErrorCode::OK;
            break;
        }
        default:
            return ErrorCode::BadFormat;
            break;
    }
}
