#ifndef _IMX_USB_H_INCLUDED
#define _IMX_USB_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif 

long get_file_size(FILE *);
int end_of_line(const char *p);
struct mach_id * imx_device(unsigned short vid, unsigned short pid, struct mach_id *p);




#ifdef __cplusplus
}
#endif 
#endif
