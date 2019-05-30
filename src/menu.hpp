#pragma once
#include "intersection.hpp"

class Menu
{
private:
    sf::Text question, answer;
    int questionNumber = 0, maxquestionsnumber=2,answerNumber=0;
    std::string questions;
    std::vector<std::string> answers;
    sf::Font font;

public:
    Menu()
    {
        font.loadFromFile("src/BebasNeue-Regular.ttf");
        question.setFont(font);
        answer.setFont(font);
        question.setCharacterSize(24);
        answer.setCharacterSize(24);
        question.setColor(sf::Color::White);
        answer.setColor(sf::Color::White);
        question.setPosition(0.0f, -50.0f);
        answer.setPosition(0.0f, 50.0f);
        nextQuestion();
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(question);
        window.draw(answer);
    }
    void nextQuestion()
    {
        answerNumber=0;
        questionNumber++;
        if(questionNumber>maxquestionsnumber)questionNumber=1;
        getqanda();
    }
    void previousQuestion()
    {
        answerNumber=0;
        questionNumber--;
        if(questionNumber<1)questionNumber=maxquestionsnumber;
        getqanda();
    }
    void nextAnswer(){
        answerNumber++;
        if(answerNumber>answers.size()-1)answerNumber=0;
        getqanda();
    }
    void previousAnswer(){
        answerNumber++;
        if(answerNumber<0)answerNumber=answers.size()-1;
        getqanda();
    }
    void getqanda(){
        switch (questionNumber)
        {
        case 1:
            questions="Left-Right: left turn lane?";
            answers = std::vector<std::string>{"yes", "no"};
            break;
         case 2:
            questions="Left-Right: right turn lane?";
            answers = std::vector<std::string>{"yes", "no"};
            break;
        }
        question.setString(questions);
        answer.setString(answers[answerNumber]);
    }

};