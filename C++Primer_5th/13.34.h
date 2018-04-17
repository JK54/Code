#include "13.34_def.h"
//--------------Message类函数定义---------

void Message::add_to_Folders(const Message &m)
{
	for(auto f : m.folders)
		f->addMsg(this);
}

Message::Message(const Message &m):contents(m.contents),folders(m.folders)
{
	add_to_Folders(m);
}

void Message::remove_from_Folders()
{
	for(auto f : folders)
		f->remMsg(this);
}

Message::~Message()
{
	remove_from_Folders();
}

void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::swap(Message &lhs,Message &rhs)
{
	using std::swap; 
	for(auto f : lhs.folders)
		f->remMsg(&lhs);
	for(auto f : rhs.folders)
		f->remMsg(&rhs);
	swap(lhs.contents,rhs.contents);
	swap(lhs.folders,rhs.folders);
	for(auto f : lhs.folders)
		f->addMsg(&lhs);
	for(auto f : rhs.folders)
		f->addMsg(&rhs);
}

Message& Message::operator=(const Message &m)
{
	remove_from_Folders();
	contents = m.contents;
	folders = m.folders;
	add_to_Folders(m);
	return *this;
}

//---------------Folder成员函数定义--------------
void Folder::remMsg(Message *mmr)
{
	msgs.erase(mmr);
}

void Folder::addMsg(Message *mmr)
{
	msgs.insert(mmr);
}

void Folder::swap(Folder &lhs,Folder &rhs)
{
	using std::swap;
	swap(lhs.msgs,rhs.msgs);
}
