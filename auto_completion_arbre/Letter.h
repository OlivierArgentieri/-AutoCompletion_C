#pragma once
#define FALSE 0
#define	TRUE 1

struct Letter
{
	char m_value;
	Letter* m_next;
	Letter* m_under;
	char m_is_final= FALSE;
};