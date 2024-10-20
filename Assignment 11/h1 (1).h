#define BUFFSIZE 1024
typedef struct
{
	char data[BUFFSIZE];
	int result,spid,cpid;
}shm_area;
shm_area *smem;
void smem_init(shm_area *smem)
{
	smem->result=-1;
	smem->spid=smem->cpid=-1;
	return;
}
