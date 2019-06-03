#pragma once
#include "intersection.hpp"

class Menu
{
private:
    sf::Text question, answer, title, tip;
    int questionNumber = 0, maxQuestionsNumber = 2, answerNumber = 0;
    std::string questions, titles, tips;
    std::vector<std::string> answers;
    sf::Font font;

public:
    Menu()
    {
        font.loadFromFile("content/BebasNeue-Regular.ttf");
        question.setFont(font);
        answer.setFont(font);
        title.setFont(font);
        tip.setFont(font);
        question.setCharacterSize(24);
        answer.setCharacterSize(24);
        title.setCharacterSize(18);
        tip.setCharacterSize(14);
        question.setColor(sf::Color::White);
        title.setColor(sf::Color::White);
        tip.setColor(sf::Color::White);
        answer.setColor(sf::Color::White);
        question.setPosition(0.0f, -25.0f);
        title.setPosition(0.0f, -100.0f);
        tip.setPosition(0.0f, 100.0f);
        answer.setPosition(0.0f, 25.0f);
        nextQuestion();
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(question);
        window.draw(answer);
        window.draw(tip);
        window.draw(title);
    }
    void nextQuestion()
    {
        answerNumber = 0;
        questionNumber++;
        if (questionNumber > maxQuestionsNumber)
            questionNumber = 1;
        getQandA();
    }
    void previousQuestion()
    {
        answerNumber = 0;
        questionNumber--;
        if (questionNumber < 1)
            questionNumber = maxQuestionsNumber;
        getQandA();
    }
    void nextAnswer()
    {
        answerNumber++;
        if (answerNumber > answers.size() - 1)
            answerNumber = 0;
        getQandA();
    }
    void previousAnswer()
    {
        answerNumber--;
        if (answerNumber < 0)
            answerNumber = answers.size() - 1;
        getQandA();
    }
    void getQandA()
    {
        switch (questionNumber)
        {
        case 1:
            titles = "Intersection Building: left and right side";
            questions = "Left turn lane?";
            answers = std::vector<std::string>{"yes", "no"};
            tips = "Use arrows to change Q and A. Changes are automaticaly saved";
            break;
        case 2:
            questions = "Right turn lane?";
            answers = std::vector<std::string>{"yes", "no"};
            break;
        }
        question.setString(questions);
        answer.setString(answers[answerNumber]);
        title.setString(titles);
        tip.setString(tips);
    }
};