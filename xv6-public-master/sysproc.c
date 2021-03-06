#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//costume syscalls

int 
sys_reverse_number(void)
{
  //code here
  return reverse_number(myproc()->tf->ecx);
}

int 
sys_trace_syscalls(int x)
{
  trace_syscalls(x);
  return 0;
}

int 
sys_get_children(int pid)
{
  return get_children(pid);
}

int 
sys_setup_trace(void){
  return setup_trace(1);
}

// Lab 3

int 
sys_level_change(int pid, int level){
  return level_change(pid, level);
}

int 
sys_set_tickets(int pid, int tickets){
  return set_tickets(pid, tickets);
}

int 
sys_change_ratios_pl(int pid, int priority_ratio, int arrival_time_ratio, int ec_ration){
  return change_ratios_pl(pid, priority_ratio, arrival_time_ratio, ec_ration);
}

int 
sys_change_ratios_sl(int pid, int priority_ratio, int arrival_time_ratio, int ec_ration){
  return change_ratios_sl(pid, priority_ratio, arrival_time_ratio, ec_ration);
}

void 
sys_htop(){
  htop();
}

//Lab 4

int 
sys_semaphore_initialize(int sid, int v, int m)
{
  return semaphore_initialize(sid,v,m);
}

int 
sys_semaphore_aquire(int sid)
{
  return semaphore_aquire(sid);
}

int 
sys_semaphore_release(int sid)
{
  return semaphore_release(sid);
}