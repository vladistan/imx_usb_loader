#ifndef _IMX_USB_H_INCLUDED
#define _IMX_USB_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif 

struct mach_id;
struct mach_id {
	struct mach_id * next;
	unsigned short vid;
	unsigned short pid;
	unsigned char file_name[256];
};

long get_file_size(FILE *);
int end_of_line(const char *p);
struct mach_id * imx_device(unsigned short vid, unsigned short pid, struct mach_id *p);

char const *conf_file_name (char const *base, int argc, char const * const *argv);

struct mach_id *parse_imx_conf (char *filename, int argc, char const *const *argv);


#ifdef __cplusplus
}
#endif 
#endif
