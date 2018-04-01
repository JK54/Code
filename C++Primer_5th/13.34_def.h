#include "comm.h"

class Folder;
class Message
{
	friend class Folder;
	public:
		explicit Message(const std::string &str = ""):contents(str){}//默认拷贝构造函数
		Message(const Message&);//拷贝构造函数
		Message& operator=(const Message&);//拷贝赋值运算符
		~Message();//析构函数
		void save(Folder&);//将Message存放到指定目录
		void remove(Folder&);//从指定目录删除消息
		void swap(Message&,Message&);//交换Message存放的目录
	private:
		std::string contents;//消息内容
		std::set<Folder*> folders;//Message存在的Folder指针set
		void add_to_Folders(const Message&);//将调用的Message添加到指定Message的Folder中
		void remove_from_Folders();//遍历folders，删除调用Message的指针
};

class Folder
{
	friend class Message;
	public:
		Folder():msgs(std::set<Message*>()){}
		Folder(const Folder&);
		Message& operator=(const Folder&);
		~Folder();
		void remMsg(Message*);//从Folder中删除Message
		void addMsg(Message*);//从Folder中增加Message
		void swap(Folder&,Folder&);//交换Folder内容

	private:
		std::set<Message*> msgs;//存放的消息指针set
};
