#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSIZE 16777216

int fileCopy(const char* src, const char* dst) {
  FILE *in, *out;
  char* buf;
  size_t len;

  if (!strcmpi(src, dst)) return 4; // ������ �纻 ������ �����ϸ� ����

  if ((in  = fopen(src, "rb")) == NULL) return 1; // ���� ���� ����
  if ((out = fopen(dst, "wb")) == NULL) { fclose(in); return 2; } // ��� ���� �����

  if ((buf = (char *) malloc(MSIZE)) == NULL) { fclose(in); fclose(out); return 10; } // ���� �޸� �Ҵ�

  while ( (len = fread(buf, sizeof(char), sizeof(buf), in)) != NULL )
    if (fwrite(buf, sizeof(char), len, out) == 0) {
      fclose(in); fclose(out);
      free(buf);
      _unlink(dst); // ������ ���� ����� ����
      return 3;
    }

  fclose(in); fclose(out);
  free(buf); // �޸� �Ҵ� ����

  return 0;
}

int main(int argc, char** argv){
	char a[1024];
	char *real_user_name;
	char *checking_user_name;
	char *start;
	int count = 0;

	start = argv[0];
	checking_user_name = strstr(start, "Users\\") + 6;
	real_user_name = strstr(checking_user_name, "\\") + 1;

	while(start != real_user_name){
		a[count] = *start;
		start++;
		count++;
	}
	a[count] = NULL;
	strcat(a, "AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\test.exe");

	count = fileCopy(argv[0], a);

	system("pause");

	return 0;
}