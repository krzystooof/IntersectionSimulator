#pragma once
#include "intersection.hpp"
#include <string>

class Menu
{
private:
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Text question, answer, title, tip;
    int questionNumber = 0, maxQuestionsNumber = 13, answerNumber = 0;
    std::string questions, titles, tips;
    std::vector<std::string> answers;
    sf::Font font;
    std::vector<LaneType> leftRight, upDown;
    std::vector<int> times;
    Intersection intersection();
    bool build = false, close = false, go = false;

public:
    Menu()
    {
        font.loadFromFile("content/Perfect DOS VGA 437.ttf");
        question.setFont(font);
        question.setCharacterSize(40);
        question.setColor(sf::Color::White);
        question.setPosition(-350.0f, -45.0f);

        answer.setFont(font);
        answer.setCharacterSize(34);
        answer.setColor(sf::Color::White);
        answer.setPosition(-350.0f, 0.0f);

        title.setFont(font);
        title.setCharacterSize(24);
        title.setColor(sf::Color::White);
        title.setPosition(-350.0f, -100.0f);

        tip.setFont(font);
        tip.setCharacterSize(18);
        tip.setColor(sf::Color::White);
        tip.setPosition(-350.0f, 50.0f);

        this->backgroundTexture.loadFromFile("content/backgroundMenu.png");
        this->backgroundTexture.setSmooth(true);
        this->background = sf::RectangleShape(sf::Vector2f(800, 200));
        this->background.setPosition(sf::Vector2f(-400, -100));
        this->background.setTexture(&this->backgroundTexture);

        nextQuestion();
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(background);
        window.draw(question);
        window.draw(answer);
        window.draw(tip);
        window.draw(title);
    }
    void nextQuestion()
    {
        switch (questionNumber)
        {
        case 1:
            if (answerNumber == 1)
            {
                leftRight.push_back(LaneType::tram);
            }
            break;
        case 2:
            if (answerNumber == 1)
            {
                leftRight.push_back(LaneType::asphaltLeft);
            }
            break;
        case 3:
            for (int i = 0; i < answerNumber+1; i++)
            {
                leftRight.push_back(LaneType::asphalt);
            }
            break;
        case 4:
            if (answerNumber == 1)
            {
                leftRight.push_back(LaneType::asphaltRight);
            }
            break;
        case 5:
            if (answerNumber == 1)
            {
                upDown.push_back(LaneType::tram);
            }
            break;
        case 6:
            if (answerNumber == 1)
            {
                upDown.push_back(LaneType::asphaltLeft);
            }
            break;
        case 7:
            for (int i = 0; i < answerNumber+1; i++)
            {
                upDown.push_back(LaneType::asphalt);
            }
            break;
        case 8:
            if (answerNumber == 1)
            {
                upDown.push_back(LaneType::asphaltRight);
            }
            build = true;
            break;
        case 9:
            times.push_back((answerNumber + 1) * 2 + 2);
            break;
        case 10:
            times.push_back((answerNumber + 1) * 2 + 2);
            break;
        case 11:
            times.push_back((answerNumber + 1) * 2 + 2);
            break;
        case 12:
        {
            times.push_back((answerNumber + 1) * 2 + 2);
            break;
        }
        case 13:
        {
            go = true;
            close = true;
            break;
        }
        }
        answerNumber = 0;
        questionNumber++;
        if (questionNumber > maxQuestionsNumber)
            questionNumber = 1;
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
            questions = "Tram lanes?";
            answers = std::vector<std::string>{"no", "yes"};
            tips = "Use arrows to change Q and A. Changes are automaticaly saved";
            break;
        case 2:
            questions = "Left turn lane?";
            answers = std::vector<std::string>{"no", "yes"};
            break;
        case 3:
            questions = "How much straight lanes?";
            answers = std::vector<std::string>{"1", "2", "3", "4"};
            break;
        case 4:
            questions = "Right turn lane?";
            answers = std::vector<std::string>{"no", "yes"};
            break;
        case 5:
            titles = "Intersection Building: up and down side";
            questions = "Tram lanes?";
            answers = std::vector<std::string>{"no", "yes"};
            tips = "Use arrows to change Q and A. Changes are automaticaly saved";
            break;
        case 6:
            questions = "Left turn lane?";
            answers = std::vector<std::string>{"no", "yes"};
            break;
        case 7:
            questions = "How much straight lanes?";
            answers = std::vector<std::string>{"1", "2", "3", "4"};
            break;
        case 8:
            questions = "Right turn lane?";
            answers = std::vector<std::string>{"no", "yes"};
            break;
        case 9:
            titles = "Intersection Building: times";
            questions = "Left - new car spawn after:";
            answers = std::vector<std::string>{"4 sec", "6 sec", "8 sec", "10 sec", "12 sec"};
            tips = "It affects all lanes on this side of the intersection";
            break;
        case 10:
            questions = "Right - new car spawn after:";
            answers = std::vector<std::string>{"4 sec", "6 sec", "8 sec", "10 sec", "12 sec"};
            break;
        case 11:
            questions = "Up - new car spawn after:";
            answers = std::vector<std::string>{"4 sec", "6 sec", "8 sec", "10 sec", "12 sec"};
            break;
        case 12:
            questions = "Down - new car spawn after:";
            answers = std::vector<std::string>{"4 sec", "6 sec", "8 sec", "10 sec", "12 sec"};
            break;
        case 13:
            titles = "Intersection Building: traffic lights";
            questions = "Traffic lights steering:";
            answers = std::vector<std::string>{"smart"};
            break;
        }
        question.setString(questions);
        answer.setString(answers[answerNumber]);
        title.setString(titles);
        tip.setString(tips);
    }
    std::vector<LaneType> getLeftRight() const
    {
        return leftRight;
    }
    std::vector<LaneType> getUpDown() const
    {
        return upDown;
    }
    std::vector<int> getTimes() const
    {
        return times;
    }
    bool getBuild() const
    {
        return build;
    }
    bool getClose() const
    {
        return close;
    }
    bool getGo() const
    {
        return go;
    }
};