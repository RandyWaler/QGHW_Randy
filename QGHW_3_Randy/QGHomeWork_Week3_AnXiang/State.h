#ifndef QGHW_State_H_INCLUDE
#define QGHW_State_H_INCLUDE

#define INT "int"

typedef enum status
{
	FALSE = 0, TRUE = 1
} Status;

void copyStr(char * str, char * copy) {
	int i;
	for (i = 0; copy[i] != '\0'&&copy[i] != '\n';i++) {
		str[i] = copy[i];
	}
	str[i] = '\0';
}

Status comparStr(char * str, char * str2) {
	int i;
	for (i = 0; str[i] != '\0'&&str[i] != '\n'&&str2[i] != '\0'&&str2[i] != '\n'; i++) {
		if (str[i] != str2[i]) {
			return FALSE;
		}
	}
	if (((str[i] == '\0' || str[i] == '\n') && (str2[i] != '\0'&&str2[i] != '\0')) || ((str2[i] == '\0' || str2[i] == '\n') && (str[i] != '\0'&&str[i] != '\0'))) {
		return FALSE;
	}
	return TRUE;
}

#endif