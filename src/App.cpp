#include "headers/App.hpp"

App::App() : isFullScreen(false) {
    scale.y = desktop.height / MinHeight;
    scale.x = desktop.width / MinWidth;

    height = MinHeight * scale.y;
    width = MinWidth * scale.x;

    window.create(sf::VideoMode(width, height), "Totally Original Social Media App", sf::Style::Close);
    if (desktop.width == 1920 && desktop.height == 1080)
        window.setPosition(sf::Vector2i(0, 0));
    else
        window.setPosition(sf::Vector2i(window.getPosition().x, 0));
    window.setFramerateLimit(60);
}

void App::toggleFullScreen() {
    if (!isFullScreen) {
        window.create(desktop, "Totally Original Social Media App", sf::Style::Fullscreen);
    }
    else {
        window.create(sf::VideoMode(width, height), "Totally Original Social Media App", sf::Style::Close);
        if (desktop.width == 1920 && desktop.height == 1080)
            window.setPosition(sf::Vector2i(0, 0));
        else
            window.setPosition(sf::Vector2i(window.getPosition().x, 0));
    }
    isFullScreen = !isFullScreen;
    window.setFramerateLimit(60);
}

void App::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
        {
            toggleFullScreen();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            for (auto& button : buttons) {
                button.second->checkClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            }
            for (auto& textField : textFields) {
                textField.second->checkClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            for (auto& textField : textFields) {
                textField.second->handleInput(event.text);
            }
        }
        else if (event.type == sf::Event::MouseWheelScrolled) {
            feed.scrollFeed(event.mouseWheelScroll);
        }
    }
}

void App::update() {
    //Update
    if (state == AppState::Login) {
        if (animations["login1"]->getActive()) {
            if (animations["login1"]->getSpeed() == 0.f) {
                animations["login1"]->setActive(0);
                rm.UnloadTexture("login1");
                animations["login2"]->setActive(1);
            }
            animations["login1"]->update();
        }
        if (animations["login2"]->getActive()) {
            if (animations["login2"]->getSpeed() == 0.f) {
                animations["login2"]->setActive(0);
                rm.UnloadTexture("login2");
                animations["login3"]->setActive(1);
                sf::sleep(sf::seconds(0.5f));
            }
            animations["login2"]->update();
        }
        if (animations["login3"]->getActive()) {
            animations["login3"]->update();
            if (animations["login3"]->getSpeed() == 0.f) {
                if (textFields["Username"]->getInput() != "" && textFields["Password"]->getInput() != "") {
                    if (buttons["Sign in"]->isActive()) {
                        if (am.signIn(textFields["Username"]->getInput(), textFields["Password"]->getInput()) == 1) {
                            startFeed();
                        }
                        else
                            buttons["Sign in"]->isActive(0);
                    }
                    else if (buttons["Sign up"]->isActive()) {
                        if (am.signUp(textFields["Username"]->getInput(), textFields["Password"]->getInput()) == 1) {
                            users[textFields["Username"]->getInput()] = new User(textFields["Username"]->getInput());
                            startFeed();
                        }
                        else
                            buttons["Sign up"]->isActive(0);
                    }
                }
            }
        }
    }
    else if (state == AppState::Feed) {
        
    }
    for (auto& textField : textFields) {
        textField.second->updateCursor();
    }
}

void App::render() {
    window.clear();
    switch (state)
    {
    case AppState::Login:
        animations["login1"]->draw(window);
        animations["login2"]->draw(window);
        animations["login3"]->draw(window);
        if (animations["login3"]->getSpeed() == 0.f) {
            for (auto& text : texts) {
                window.draw(text.second);
            }
            for (auto& textField : textFields) {
                textField.second->draw(window);
            }
            for (auto& button : buttons) {
                button.second->draw(window);
            }
        }
        break;
    case AppState::Feed:
        if (zoom > -5.f) {
            animations["login3"]->draw(window);
            sf::View view = window.getView();
            view.zoom(zoom);
            window.setView(view);
            zoom -= 0.0075f;
        }
        else {
            window.setView(window.getDefaultView());
            window.draw(background);
            feed.drawFeed(window);
        }
        break;
    case AppState::Settings:

        break;
    default:
        break;
    }
    window.display();
}

void App::populateUsers() {
    for (auto& account : json["accounts"]) {
        users[account["username"]] = new User(account["username"]);
        if (account.find("posts") != account.end()) {
            for (auto& post : account["posts"]) {
                std::string title = post["title"];
                std::string content = post["content"];
                std::string date = post["date"];
                int likes = post["likes"];
                std::vector<std::string> likedBy = post["LikedBy"].get<std::vector<std::string>>();
                std::vector<Comment> comments;
                for (auto& comment : post["comments"]) {
                    std::string username = comment["username"];
                    std::string content = comment["content"];
                    comments.push_back(Comment(username, content));
                }
                users[account["username"]]->AddPost(Post(account["username"], rm.CreateText(title), rm.CreateText(content), Post::Activity::none, likedBy, comments));
            }
        }       
    }
}

void App::startFeed() {
    feed = Feed::GetInstance(users[textFields["Username"]->getInput()]);
    feed.populateFeed(users);
    state = AppState::Feed;
}

void App::init() {
    json = am.getJson();
    populateUsers();
    background.setPosition(sf::Vector2f(0, 0));
    background.setFillColor(sf::Color(28, 28, 30));
    rm.LoadFont("OpenSans");
    texts["login"] = rm.CreateText("Account Login", sf::Vector2f(750.f, 420.f));
    textFields["Username"] = new TextInputField(750.f, 460.f, 480.f, 50.f, rm.CreateText("Enter Username"));
    textFields["Password"] = new TextInputField(750.f, 560.f, 480.f, 50.f, rm.CreateText("Enter Password"));
    buttons["Sign in"] = new Button(1000.f, 680.f, 200.f, 50.f, rm.CreateText("Login"));
    buttons["Sign up"] = new Button(750.f, 680.f, 200.f, 50.f, rm.CreateText("Register"));
    rm.LoadTexture("login1");
    rm.LoadTexture("login2");
    rm.LoadTexture("login3");
    animations["login1"] = new Animation(rm.CreateSprite("login1"), "login1", 0.17f, 0, 1, sf::Vector2f(2.4f, 2.25f));
    animations["login2"] = new Animation(rm.CreateSprite("login2"), "login2", 0.17f, 0, 0, sf::Vector2f(2.4f, 2.25f));
    animations["login3"] = new Animation(rm.CreateSprite("login3"), "login3", 0.3f, 0, 0, sf::Vector2f(2.4f, 2.25f));
}

void App::end() {
    for (auto& animation : animations) {
        delete animation.second;
    }
    for (auto& button : buttons) {
        delete button.second;
    }
    for (auto& textField : textFields) {
        delete textField.second;
    }
    for (auto& user : users) {
        delete user.second;
    }
    rm.ClearAll();
}

void App::Run() {
    static App app;
    app.init();
    while (app.window.isOpen())
    {
        app.handleEvents();
        app.update();
        app.render();
    }
    app.end();
}