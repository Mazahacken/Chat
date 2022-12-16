#include "Chat.h"
#include "User.h"
#include <iostream>

void Chat::login()
{
	std::string login, password;
	char operation;

	do
	{
		std::cout << "login: ";
		std::cin >> login;
		std::cout << "password: ";
		std::cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getPassword()))
		{
			currentUser_ = nullptr;

			std::cout << "login failed..." << std::endl;
			std::cout << "(0)exit or (any key)repeat: ";
			std::cin >> operation;

			if (operation == '0')
				break;
		}
	} while (!currentUser_);
}

void Chat::singUp()
{
	std::string login, password, name;

	std::cout << "login: ";
	std::cin >> login;
	std::cout << "password: ";
	std::cin >> password;
	std::cout << "name: ";
	std::cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	if (getUserName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	currentUser_ = std::make_shared<User>(user);
}

void Chat::showChat() const
{
	std::string from;
	std::string to;

	std::cout << "--- Chat ---" << std::endl;

	for (auto &mess : messages_)
	{
		if (currentUser_->getLogin() == mess.getFrom() || currentUser_->getLogin() == mess.getTo() || mess.getTo() == "all")
		{
			from = (currentUser_->getLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getTo())->getName();
			if (mess.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (currentUser_->getLogin() == mess.getTo() ? "me" : getUserByLogin(mess.getTo())->getName());
			}

			std::cout << "Message from " << from << " to " << to << std::endl;
			std::cout << "text: " << mess.getText() << std::endl;
		}
		std::cout << "------------" << std::endl;
		
		std::cout << "Message from " << from << " to " << to << std::endl;
		std::cout << "text: " << mess.getText() << std::endl;
	}
	
}

void Chat::showAllUsersName() const
{
	std::cout << "--- Users ---" << std::endl;
	for (auto& user : users_)
	{
		std::cout << user.getName();

		if (currentUser_->getLogin() == user.getLogin())
			std::cout << "(me)";

		std::cout << std::endl;
	}
	std::cout << "-------------" << std::endl;
}

void Chat::addMessage()
{
	std::string to, text;

	std::cout << "To (name or all): ";
	std::cin >> to;
	std::cout << "Text: ";
	std::cin.ignore();
	getline(std::cin, text);

	if (!(to == "all" || getUserName(to)))
	{
		std::cout << "error send message: cann`t find " << to << std::endl;
		return;
	}

	if (to == "all")
		messages_.push_back(Message{ currentUser_->getLogin(), "all", text });
	else
		messages_.push_back(Message{ currentUser_->getLogin(),getUserName(to)->getLogin(),text });

}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : users_)
	{
		if (login == user.getLogin())
			return std::make_shared<User>(user);
	}

	return nullptr;
}

std::shared_ptr<User> Chat::getUserName(const std::string& name) const
{
	for (auto& user : users_)
	{
		if (name == user.getName())
		{
			return std::make_shared<User>(user);
		}
	}
	return nullptr;;
}

void Chat::start()
{
	isChatWork_ = true;
}

void Chat::showLoginMenu()
{
	currentUser_ = nullptr;

	char operation;

	do
	{
		std::cout << "\033[33m" << "(1)Login" << std::endl;
		std::cout << "(2)SignUp" << std::endl;
		std::cout << "(0)Shutdown" << std::endl;
		std::cout << "\33[36m" << ">> " << "\33[0m";
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			login();
			break;
		case '2':
			try
			{
				singUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case '0':
			isChatWork_ = false;
			break;
		default:
			std::cout << "1 or 2..." << std::endl;
			break;
		}
	} while (!currentUser_ && isChatWork_);

}

void Chat::showUserMenu()
{
	char operation;

	std::cout << "Hi," << currentUser_ << std::endl;

	while (currentUser_) {
		std::cout << "Menu: (1)Show chat | (2)Add message | (3)Users | (0)Logout";

		std::cout << std::endl
			<< ">> ";
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case '0':
			currentUser_ = nullptr;
			break;
		default:
			std::cout << "unknowm choice.." << std::endl;
			break;
		}
	}


}
