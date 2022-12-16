#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"

struct UserLoginExp
{
	const char* what() const noexcept override { return "error login"; }
};

struct UserNameExp 
{ 
	const char* what() const noexcept override { return "error name"; }
};

class Chat
{
	bool isChatWork_ = false;
	std::vector<User> users_;
	std::vector<Message> messages_;
	std::shared_ptr<User> currentUser_ = nullptr;

	void login();
	void singUp();
	void showChat() const;
	void showAllUsersName() const;
	void addMessage();
	std::vector<User>& getAllUsers() { return users_; }
	std::vector<Message>& getAllMessages() { return messages_; }
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	std::shared_ptr<User> getUserName(const std::string& name) const;

public:
	void start();
	bool isChatWork() const { return isChatWork_; }
	std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void showLoginMenu();
	void showUserMenu();
};