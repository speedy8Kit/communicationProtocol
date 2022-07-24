#pragma once

class ACExchangeInterface
{
public:
	virtual int open() = 0;
	virtual int close() = 0;
	virtual int readBuff(char* buf) = 0;
	virtual int writeBuff(const char* m_buff, unsigned int len_buf) = 0;
private:
};

