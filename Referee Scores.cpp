#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#define PeopleNum 12
using namespace std;
struct Competitors{
    char Number[10];
    char Name[10];
    char Sex[10];
    int Class;
    char QQnumber[11];
    float AvgScore;
};
struct Referees{
    char Name[10];
    float Score[PeopleNum];
};
bool cmp1(int a, int b)
{
    return a>b;
}
int cmp2(const void *a,const void *b)
{
    struct Competitors *x = (struct Competitors*)a;
    struct Competitors *y = (struct Competitors*)b;
    return (x->AvgScore < y->AvgScore);
}
int main()
{
    int score[7];
    float sum = 0;
    struct Competitors Competitors[PeopleNum];
    struct Referees Referees[7];
    ifstream Competitor("/Users/s20181106115/Desktop/Competitor.txt");
    ifstream Referee("/Users/s20181106115/Desktop/Referee.txt");
    ofstream Result("/Users/s20181106115/Desktop/Result.csv");
    if(Referee.is_open())
    {
        for(int i = 0; i < 7; i++)
        {
            Referee >> Referees[i].Name;
            for(int j = 0; j < PeopleNum; j++)
            {
                Referee >> Referees[i].Score[j];
            }
        }
        for(int i = 0; i < PeopleNum; i++)
        {
            for(int j = 0; j < 7; j++)
            {
                score[j] = Referees[j].Score[i];
            }
            sort(score, score + 7, cmp1);
            for(int k = 1; k < 6; k++)
            {
                sum += score[k];
            }
            Competitors[i].AvgScore = sum / 5;
            sum = 0;
        }
        Referee.close();
    }
    if(Competitor.is_open())
    {
        for(int i = 0; i < PeopleNum; i++)
        {
            Competitor >> Competitors[i].Number
            >> Competitors[i].Name
            >> Competitors[i].Sex
            >> Competitors[i].Class
            >> Competitors[i].QQnumber;
        }
        Competitor.close();
    }
    if(Result.is_open())
    {
        qsort(Competitors, PeopleNum, sizeof(Competitors[0]), cmp2);
        Result << left << setw(5) << "Number "
        << left << setw(8) << "Name "
        << left << setw(8) << "Sex "
        << left << setw(3) << "Class "
        << left << setw(13) << "QQnumber "
        << left << setw(8) << "Score "
        << left << setw(5) << "Rank "
        << endl;
        for(int i = 0; i < PeopleNum; i++)
        {
            Result << left << setw(5) << Competitors[i].Number << " "
            << left << setw(8) << Competitors[i].Name <<" "
            << left << setw(8) << Competitors[i].Sex <<" "
            << left << setw(3) << Competitors[i].Class <<" "
            << left << setw(13) << Competitors[i].QQnumber <<" "
            << left << setw(8) << setprecision(2)<< fixed << Competitors[i].AvgScore <<" "
            << left << setw(5) << i + 1
            << endl;
        }
        Result.close();
    }
    return 0;
}
