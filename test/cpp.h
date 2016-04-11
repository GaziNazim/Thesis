/************************************************************************/
/* CSIM is copyrighted by						*/
/*	Microelectronics and Computer Technology Corporation, 1985,	*/
/*		1986, 1987, 1988, 1989, 1990, 1991, 1992		*/
/*	All rights are reserved.					*/
/*									*/
/************************************************************************/
// extended header file for CSIM/C++ programs

// #define LOG_SW

#ifndef _CPPH
#define _CPPH
/* #define CPP */ /* jorgeg - comment out for hpgnu & solaris bcw*/

#include <stdlib.h>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#ifndef STL
#define event csim_event
#define facility csim_facility
#define message csim_message
#define mailbox csim_mailbox
#define storage csim_storage
#define buffer csim_buffer
#define table csim_table
#define qtable csim_qtable
#define meter csim_meter
#define box csim_box
#define stream csim_stream
#define stream2 csim_stream2
#define set csim_set
#define identity csim_identity
#define priority csim_priority
#endif

class process_class;
typedef process_class* process_class_t;
class process;
typedef process* process_t;
class message;
typedef message* message_t;
class csim_event;
class global_event;
class event_set;
class csim_facility;
class facility_ms;
class facility_set;
class multi_facility;
class csim_mailbox;
class global_mailbox;
class csim_storage;
class csim_buffer;
class storage_set;
class csim_table;
class permanent_table;
class histogram;
class permanent_histogram;
class csim_qtable;
class qhistogram;
class csim_meter;
class csim_box;
class csim_stream;

/* jorgeg - used by hpgnu
#ifndef __STDC__
#define __STDC__
#endif */

extern "C" {
#include "csim.h"

void xerr(long);
}

//class xcsim_class {
//public:
//	xcsim_class();
//};

class process_class {
protected:
	CLASS cl;
public:
	CLASS ptr()			{ return(cl);}
	process_class()		{ cl = create_process_class("def",this);}
	process_class(const char *s)	{ cl = create_process_class(s,this); }
	process_class(const char *s, long flag) {cl = create_process_class_perm(s, this); }
	~process_class()	{ if(cl != NIL) {::delete_process_class(cl);cl = NIL;}}
	void reset()		{ ::reset_process_class(cl);}
	void set_process_class(){ ::set_process_class(cl); }
	void set_name(const char* s)	{ ::set_name_process_class(cl, s); }
	long id()			{ return(::class_id(cl)); }
	CLASS* get_addr()	{ return(&cl);}
	const char* name()	{ return(::class_name(cl));}
	long cnt()			{ return(::class_cnt(cl));}
	long holdcnt()		{ return(::class_holdcnt(cl));}
	double holdtime()	{ return(::class_holdtime(cl));}
	double lifetime()	{ return(::class_lifetime(cl));}
	long index()		{ return(::class_id(cl));}
};

process_class* current_class();/* jorgeg - comment out for hpgnu */

class process {
protected:
public:
	process_t next()		{return (process_t) next_process((PROCESS_PTR)this);}
	long priority()			{return get_process_priority((PROCESS_PTR)this);}
	void set_priority(long n)	{set_process_priority((PROCESS_PTR)this, n);}
	long identity()			{ return get_process_identity((PROCESS_PTR)this);}
	char* name()			{ return get_process_name((PROCESS_PTR)this);}
	void* get_struct()		{ return get_process_struct((PROCESS_PTR) this);}
	void set_struct(void* sptr)	{set_process_struct((PROCESS_PTR) this, sptr);}
	void restart()			{ restart_process((PROCESS_PTR) this);}
};

class csim_event {
protected:
	EVENT ev;
	csim_event(long flg)		{if(flg != -1) xerr(25);}
public:
	csim_event()			{ ev = create_event("def"); }
	csim_event(const char* s)		{ ev = create_event(s); }
	csim_event(EVENT e)		{ev = e;}
	~csim_event()		{ if(ev != NIL) { ::delete_event(ev); ev = NIL;} }
	void reset()		{ ::reset_event(ev);}
	void monitor()		{ event_monitor(ev);}
	EVENT* get_addr()	{ return(&ev);}
	void clear()		{ ::csim_clear(ev); }
	long event_qlen()	{ return(::event_qlen(ev)); }
	void queue()		{ ::csim_queue(ev); }
	long queue_cnt()		{ return(::queue_cnt(ev)); }
	void set()		{ ::csim_set(ev); }
	void set_name(const char* s)	{ ::set_name_event(ev, s); }
	const char *name()			{ return ::event_name(ev); } /* jorgeg not used in hpgnu */
	long state()		{ return(::csim_state(ev)); }
	long timed_queue(double tm) { return(::timed_queue(ev, tm)); }
	long timed_wait(double tm)	{ return(::timed_wait(ev, tm)); }
	void wait()					{ csim_wait(ev); }
	long wait_cnt()				{ return(::wait_cnt(ev)); }
	double queue_sum()			{ return(::event_queue_sum(ev));}
	double wait_sum()			{ return(::event_wait_sum(ev));}
	long queue_delay_count()	{ return(::event_queue_delay_count(ev));}
	long wait_delay_count()		{ return(::event_wait_delay_count(ev));}
	double queue_length()	{ return(::event_queue_length(ev));}
	double wait_length()	{ return(::event_wait_time(ev));}
	double queue_time()	{ return(::event_queue_time(ev));}
	double wait_time()	{ return(::event_wait_time(ev));}
	long queue_count()	{ return(::event_queue_count(ev));}
	long wait_count()		{ return(::event_wait_count(ev));}
	long set_count()		{ return(::event_set_count(ev));}
	process_t first_wait_process()				{return (process_t)event_first_wait_process(ev);}
	process_t last_wait_process()				{return (process_t)event_last_wait_process(ev);}
	process_t remove_wait_process(process_t pp)	{return (process_t)event_remove_wait_process(ev, (PROCESS_PTR)pp);}
	void insert_wait_process(process_t pp)		{event_insert_wait_process(ev, (PROCESS_PTR)pp);}
	process_t first_queue_process()				{return (process_t)event_first_queue_process(ev);}
	process_t last_queue_process()				{return (process_t)event_last_queue_process(ev);}
	process_t remove_queue_process(process_t pp)	{return (process_t)event_remove_queue_process(ev, (PROCESS_PTR)pp);}
	void insert_queue_process(process_t pp)		{event_insert_queue_process(ev, (PROCESS_PTR)pp);}
};

class global_event : public csim_event {
public:
	global_event();
	global_event(const char*);
};

class event_set {
protected:
	long numEvents;
	csim_event* ev;
public:
	event_set(const char*, long);
	event_set();
	~event_set();
	const char *name()	{ return(::event_set_name(ev->get_addr()));}
	long queue_any()	{ return(::queue_any(ev->get_addr())); }
	long wait_any()		{ return(::wait_any(ev->get_addr())); }
	long timed_wait_any(double t) {return(::timed_wait_any(ev->get_addr(), t)); }
	long timed_queue_any(double t) {return(::timed_queue_any(ev->get_addr(), t)); }
	long num_events()				{return(::num_events(ev->get_addr())); }
	void monitor()					{::event_set_monitor(ev->get_addr());}
	csim_event& operator[](long i){ return(ev[i]); }
};

class csim_facility {
protected:
	FACILITY f;
	csim_facility(long flg)	{ if(flg != -1) xerr(25); }
public:
	csim_facility()		{ f = create_facility("def"); }
	csim_facility(const char* s)	{ f = create_facility(s); }
	~csim_facility()	{if(f != NIL) { ::delete_facility(f); f = NIL;}}
	FACILITY* get_addr(){ return(&f); }
	void reset()		{ ::reset_facility(f);}
	long num_busy()		{ return(::num_busy(f)); }
	long qlength()		{ return(::qlength(f)); }
	void release()		{ ::release(f); }
	void release_server(long i) { ::release_server(f, i); }
	long reserve()		{ return(::reserve(f)); }
	long status()		{ return(::csim_status(f)); }
	void set_name(const char* s)	{ ::set_name_facility(f, s);}
	void set_servicefunc(SF func){ ::set_servicefunc(f, func); }
	void set_loaddep(double arr[], long n) {::set_loaddep(f, arr, n);}
	long timed_reserve(double t)	{ return(::timed_reserve(f, t));}
	void synchronous(double ph, double per) { ::synchronous_facility(f, ph, per); }
	void collect_class_facility(){ ::collect_class_facility(f);}
	TIME use(double t)	{ return(::use(f, t)); }
	double timeslice()	{ return(::timeslice(f)); }
	void set_timeslice(double t) { ::set_timeslice(f, t); }
	long completions()	{ return(::completions(f)); }
	long preempts()		{ return(::preempts(f));}
	const char* name()	{ return(::facility_name(f));}
	long num_servers()	{ return(::num_servers(f));}
	double qlen()		{ return(::qlen(f)); }
	double resp()		{ return(::resp(f)); }
	double serv()		{ return(::serv(f)); }
	const char* service_disp()	{ return(::service_disp(f));}
	double tput()		{ return(::tput(f)); }
	double util()		{ return(::util(f)); }
	long server_completions(long n)	{ return(::server_completions(f,n));}
	double server_serv(long n)	{ return(::server_serv(f, n));}
	double server_tput(long n)	{ return(::server_tput(f,n));}
	double server_util(long n)	{ return(::server_util(f,n));}
	long class_completions(process_class_t c)	{ return(::class_completions(f, c->ptr()));}
	long class_qlength(process_class_t c)	{ return(::class_qlength(f, c->ptr())); }
	double class_qlen(process_class_t c)	{ return(::class_qlen(f, c->ptr()));}
	double class_resp(process_class_t c)	{ return(::class_resp(f, c->ptr()));}
	double class_serv(process_class_t c)	{ return(::class_serv(f, c->ptr()));}
	double class_tput(process_class_t c)	{ return(::class_tput(f, c->ptr()));}
	double class_util(process_class_t c)	{ return(::class_util(f, c->ptr()));}
//  queue manger routines
	process_t first_process()	{return (process_t)facility_first_process(f);}
	process_t last_process()	{return (process_t)facility_last_process(f);}
	process_t remove_process(process_t ptr)	{return (process_t)facility_remove_process(f, (PROCESS_PTR) ptr);}
	void insert_process(process_t ptr)	{facility_insert_process(f, (PROCESS_PTR) ptr);}
};

class facility_ms : public csim_facility {
public:
	facility_ms(const char*, long);
};

class facility_set {
protected:
	csim_facility* f;
public:
	facility_set(const char*, long);
	facility_set();
	~facility_set();
	csim_facility& operator[](long i) { return(f[i]); }
};


extern "C" char* xretmsg(MSG_PTR);

class csim_message {
protected:
public:
	~csim_message()				{xretmsg((MSG_PTR)this);}
	message_t next()			{return (message_t)next_msg((MSG_PTR)this);}
	long content()				{return msg_content((MSG_PTR) this);}
	void operator delete(void* p){}
};

class csim_mailbox {
protected:
	MBOX mb;
	csim_mailbox(long flg)	{ if(flg != -1) xerr(25); }
public:
	csim_mailbox()		{ mb = create_mailbox("def"); }
	csim_mailbox(const char* nm)	{ mb = create_mailbox(nm); }
	~csim_mailbox()		{if(mb != NIL) {::delete_mailbox(mb); mb = NIL;}}
	MBOX * get_addr()	{return &mb;}
	void reset()		{::reset_mailbox(mb);}
	long queue_cnt()	{return (::mailbox_queue_cnt(mb));}
	long msg_cnt()		{ return(::msg_cnt(mb)); }
	void receive(long* msg)	{ ::csim_receive(mb, msg); }
	long timed_receive(long *msg, double t)
				{ return(::timed_receive(mb, msg, t)); }
	void send(long msg)	{ ::csim_send(mb, msg); }
	void synchronous_send(long msg)	{::synchronous_send(mb, msg);}
	long timed_synchronous_send(long msg, double t) {return ::timed_synchronous_send(mb, msg, t);}
	void set_name(const char* s)	{ ::set_name_mailbox(mb, s); }
	const char* name()		{ return(::mailbox_name(mb)); }
	double proc_sum()						{return ::mailbox_proc_sum(mb);}
	long proc_delay_count()					{return ::mailbox_proc_delay_count(mb);}
	long proc_count()						{return ::mailbox_proc_count(mb);}
	double proc_length()					{return ::mailbox_proc_length(mb);}
	double proc_time()						{return ::mailbox_proc_time(mb);}
	double msg_sum()						{return ::mailbox_msg_sum(mb);}
	long msg_delay_count()					{return ::mailbox_msg_delay_count(mb);}
	long msg_count()						{return ::mailbox_msg_count(mb);}
	double msg_length()						{return ::mailbox_msg_length(mb);}
	double msg_time()						{return ::mailbox_msg_time(mb);}
	void monitor()							{::mailbox_monitor(mb);}

	process_t first_process()				{return (process_t)mailbox_first_process(mb);}
	process_t last_process()				{return (process_t)mailbox_last_process(mb);}
	process_t remove_process(process_t pp)	{return (process_t)mailbox_remove_process(mb, (PROCESS_PTR)pp);}
	void insert_process(process_t pp)		{mailbox_insert_process(mb, (PROCESS_PTR)pp);}

	message_t first_message()				{return (message_t)mailbox_first_msg(mb);}
	message_t last_message()				{return (message_t)mailbox_last_msg(mb);}
	message_t remove_message(message_t m)	{return (message_t)mailbox_remove_msg(mb, (MSG_PTR)m);}
	void insert_message(message_t m)		{mailbox_insert_msg(mb, (MSG_PTR)m);}
};

class global_mailbox : public csim_mailbox {
public:
	global_mailbox();
	global_mailbox(const char *);
};

class mailbox_set {
protected:
	long numMailboxes;
	csim_mailbox *mb;
	csim_event *evnt;
public:
	mailbox_set(char * nm, long n);
	mailbox_set();
	~mailbox_set();
	const char* name()			{return ::mailbox_set_name(mb->get_addr());}
	long receive_any(long *msg)	{return ::receive_any(mb->get_addr(), msg); }
	long timed_receive_any(long *msg, double t) {return ::timed_receive_any(mb->get_addr(), msg, t);}
	long num_msgs()				{return ::mailbox_set_num_msgs(mb->get_addr());}
	void monitor_event()		{::event_monitor(::mailbox_set_event(mb->get_addr()));}
	event* get_event()			{return evnt;}
	void monitor();
	csim_mailbox& operator[](long i) {return mb[i];}
};

class csim_storage {
protected:
	STORE s;
	csim_storage(long flg)	{ if(flg != -1) xerr(25); }
public:
	csim_storage()		{ s = create_storage("def", 1l); }
	csim_storage(const char* nm, long sz){ s = create_storage(nm, sz); }
	~csim_storage()		{if(s != NIL) { ::delete_storage(s); s = NIL;} }
	STORE* get_addr()	{ return(&s); }
	void reset()		{ ::reset_storage(s);}
	void add_store(long sz)	{ ::add_more_store(s, sz); }
	void remove_store(long sz) {::remove_store(s, sz); }
	void synchronous(double ph, double per) { ::synchronous_storage(s, ph, per); }
	void set_name(const char* nm)	{ ::set_name_storage(s, nm); }
	void allocate(long m)	{ ::alloc(s, m); }
	void alloc(long m)		{ ::alloc(s, m);}
	long avail()		{ return(::avail(s)); }
	void deallocate(long m)	{ ::dealloc(s, m); }
	void dealloc(long m)	{ ::dealloc(s, m); }
	const char* name()		{ return(::storage_name(s));}
	long capacity()		{ return(::storage_capacity(s));}
	double request_amt()	{ return(::storage_request_amt(s));}
	double request_total(){ return(::storage_request_total(s));}
	double release_total(){ return(::storage_release_total(s));}
	long number_amt()	{ return(::storage_number_amt(s));}
	TIME busy_amt()		{ return(::storage_busy_amt(s));}
	TIME waiting_amt()	{ return(::storage_waiting_amt(s));}
	long request_cnt()	{ return(::storage_request_cnt(s));}
	long release_cnt()	{ return(::storage_release_cnt(s));}
	long queue_cnt()	{ return(::storage_queue_cnt(s));}
	long qlength()		{ return(::storage_qlength(s));}
	double time()		{ return(::storage_time(s));}
	long timed_allocate(long m, double t)
					{ return(::timed_allocate(m, s, t)); }
	long timed_alloc(long m, double t) {return(::timed_alloc(s, m, t));}
//	queue manager routines
	process_t first_process()	{return (process_t)storage_first_process(s);}
	process_t last_process()	{return (process_t)storage_last_process(s);}
	process_t remove_process(process_t ptr)	{return (process_t)storage_remove_process(s, (PROCESS_PTR) ptr);}
	void insert_process(process_t ptr)	{storage_insert_process(s, (PROCESS_PTR) ptr);} 
};

class storage_set {
	csim_storage* s;
public:
	storage_set(const char*, long, long);
	storage_set();
	~storage_set();
	csim_storage& operator[](long i){ return(s[i]); }
};

class csim_buffer {
	BUFFER buf;
	BUFFER setup(const char *nm, const long amt);
public:
	csim_buffer()					{buf = setup("def", 5);}
	csim_buffer(const char *nm, const long amt) {buf = setup(nm, amt);}
	~csim_buffer()					{if(buf != NIL) delete_buffer(buf); buf = NIL;}
	void reset()					{::reset_buffer(buf);}
	void put(const long amt)		{buffer_put(buf, amt);}
	void get(const long amt)		{buffer_get(buf, amt);}
	long timed_put(const long amt, double t) {return buffer_timed_put(buf, amt, t);}
	long timed_get(const long amt, double t) {return buffer_timed_get(buf, amt, t);}
	long current()					{return buffer_current(buf);}
	long size()						{return buffer_size(buf);}
	long get_total()				{return buffer_get_total(buf);}
	long put_total()				{return buffer_put_total(buf);}
	long get_count()				{return buffer_get_count(buf);}
	long put_count()				{return buffer_put_count(buf);}
	double get_timeQueue()			{return buffer_get_timeQueue(buf);}
	double put_timeQueue()			{return buffer_put_timeQueue(buf);}
	void add_space(const long amt)	{buffer_add_space(buf, amt);}
	void remove_space(const long amt){buffer_remove_space(buf, amt);}
	char* name()					{return buffer_name(buf);}
	long get_current_count()		{return buffer_get_current_count(buf);}
	long put_current_count()		{return buffer_put_current_count(buf);}
	process_t put_first_process()	{return (process_t)buffer_put_first_process(buf);}
	process_t put_last_process()	{return (process_t)buffer_put_last_process(buf);}
	process_t put_remove_process(process_t p) {return (process_t)buffer_put_remove_process(buf, (PROCESS_PTR)p);}
	void put_insert_process(process_t p) {buffer_put_insert_process(buf, (PROCESS_PTR)p);}
	process_t get_first_process()	{return (process_t)buffer_get_first_process(buf);}
	process_t get_last_process()	{return (process_t)buffer_get_last_process(buf);}
	process_t get_remove_process(process_t p) {return (process_t)buffer_get_remove_process(buf, (PROCESS_PTR)p);}
	void get_insert_process(process_t p) {buffer_get_insert_process(buf, (PROCESS_PTR)p);}
};

class csim_table {
protected:
	TABLE t;
	HISTO h;
	csim_table(long flg)		{ if(flg != -1) xerr(25); }
public:
	csim_table()				{ t = create_table("def"); h = NIL;}
	csim_table(const char* lgnd)	{ t = create_table(lgnd); h = NIL;}
	csim_table(csim_table* tbl)	{ t = (TABLE)tbl;}
	csim_table(const char* lgnd, long n, double lo, double hi)
			{ t = create_table(lgnd); table_histogram(t, n, lo, hi); h = table_hist(t);}  /* JAB */
	~csim_table()            {if(t != NIL) { ::delete_table(t); t = NIL; h = NIL;} }
	void record(double x) { ::tabulate(t, x); }
	void tabulate(double x){ ::tabulate(t, x) ;}
	void report()		{ ::report_table(t); }
	void add_histogram (long n, double lo, double hi) { ::table_histogram(t, n, lo, hi); h = table_hist(t); }
	void confidence()	{ ::table_confidence(t);}
	void moving_window(long n)	{::set_moving_table(t, n); }
	const char *name()		{return(::table_name(t));}
	long window_size()	{return(::table_window_size(t));}
	long cnt()          { return(::table_cnt(t)); }
	double min()        { return(::table_min(t)); }
	double max()        { return(::table_max(t)); }
	double sum()		{ return(::table_sum(t)); }
	double sum_square()	{ return(::table_sum_square(t)); }
	double mean()       { return(::table_mean(t)); }
	double range()      { return(::table_range(t)); }               /* JAB */
	double var()		{ return(::table_var(t)); }
 	double stddev()     { return(::table_stddev(t));}               /* JAB */
	double cv()         { return(::table_cv(t));}                   /* JAB */
	
   /* JAB */
	
   long    hist_num ()                    { return (::table_histogram_num (t)); }
   double  hist_low ()                    { return (::table_histogram_low (t)); }
   double  hist_high ()                   { return (::table_histogram_high (t)); }
   double  hist_width ()                  { return (::table_histogram_width (t)); }
   long    hist_total ()                  { return (::table_histogram_total (t)); }
   long    hist_bucket (long i)           { return (::table_histogram_bucket (t, i)); }

   long    batch_size ()                  { return (::table_batch_size (t)); }
   long    batch_count ()                 { return (::table_batch_count (t)); }
   long	   converged ()                   { return (::table_converged (t)); }
   double  conf_mean ()                   { return (::table_conf_mean (t)); }
   double  conf_halfwidth (double level)  { return (::table_conf_halfwidth (t, level)); }
   double  conf_lower (double level)      { return (::table_conf_lower (t, level)); }
   double  conf_upper (double level)      { return (::table_conf_upper (t, level)); }
   double  conf_accuracy (double level)   { return (::table_conf_accuracy (t, level)); }

	void set_name(const char* nm)	{ ::set_name_table(t, nm); }	/* JAB */
	void reset()		{ ::reset_table(t); }

	long size() 		 { return(::table_window_size(t)); }
	void run_length(double accur, double conf_lev, double max_tm) { ::table_run_length(t, accur, conf_lev, max_tm);}

	/* HDS */
	void set_moving(long n)	{::set_moving_table(t, n); }
	long moving_window()	{return(::table_window_size(t));}
};

class histogram : public csim_table {
protected:
public:
	histogram(const char *nm, long n, double lo, double hi)  : csim_table(nm, n, lo, hi) {};
/*	long cnt()          { return(::table_cnt(h)); }
	const char* name()		{ return(::table_name(t)); }	*/
	
   long    num ()                    { return (::table_histogram_num (t)); }
   double  low ()                    { return (::table_histogram_low (t)); }
   double  high ()                   { return (::table_histogram_high (t)); }
   double  width ()                  { return (::table_histogram_width (t)); }
   long    total ()                  { return (::table_histogram_total (t)); }
   long    bucket (long i)           { return (::table_histogram_bucket (t, i)); }	
};

class permanent_table : public csim_table {
public:
	permanent_table() : csim_table(-1)	{ t = create_permanent_table("def"); h = NIL;}
	permanent_table(const char *nm) : csim_table(-1) { t = create_permanent_table(nm); h = NIL;}
	permanent_table(const char *nm, long n, double lo, double hi) : csim_table(-1)
			{t = create_permanent_table(nm); table_histogram(t, n, lo, hi); h = table_hist(t); }
};

class permanent_histogram : public permanent_table {
public:	
	permanent_histogram(const char*nm, long n, double lo, double hi)  :  permanent_table(nm, n, lo, hi) {};
};

class csim_qtable {
protected:
	QTABLE qt;
	HISTO h;
	csim_qtable(long flg)	{ if(flg != -1) xerr(25); }
public:
	csim_qtable()			{ qt = create_qtable("def"); h = NIL; }
	csim_qtable(csim_qtable* qtbl){ qt = (QTABLE)qtbl; h = NIL;}
	csim_qtable(const char* lgnd)	{ qt = create_qtable(lgnd); h = NIL; }	/* JAB */
	csim_qtable(const char* lgnd, long n, long lo, long hi)
			{ qt = create_qtable(lgnd); qtable_histogram(qt, n, lo, hi); h = qtable_hist(qt);}
	~csim_qtable()			{if(qt != NIL) { ::delete_qtable(qt); qt = NIL; h = NIL;} }
	void note_entry()	{ ::note_entry(qt); }
	void note_exit()	{ ::note_exit(qt); }
	void note_value(long n)	{::note_value(qt, n);}
	void record_value(double x)	{::record_value(qt, x);}
	void set_initial_value(double x) {::set_initial_value(qt, x);}
	void report()		{ ::report_qtable(qt); }
	void report_dbl()	{ ::report_qtable_dbl(qt); }
	void add_histogram (long n, long lo, long hi)
			{ ::qtable_histogram(qt, n, lo, hi); h = qtable_hist(qt); }
	void confidence ()	{ ::qtable_confidence(qt); }
	void run_length(double accur, double conf_level, double max_time)
			{::qtable_run_length(qt, accur, conf_level, max_time);}
	void moving_window(long n) { ::qtable_moving_window(qt, n); }
	const char* name()		{ return(::qtable_name(qt)); }
	long window_size()	{ return(::qtable_window_size(qt));}
	long entries()		{ return(::qtable_entries(qt));}
	long exits()		{ return(::qtable_exits(qt));}
	long min()			{ return(::qtable_min(qt));}
	long max()			{ return(::qtable_max(qt));}
	long range()		{ return(::qtable_range(qt));}
	long initial()		{ return(::qtable_initial(qt));}
	long current()		{ return(::qtable_current(qt));}
	double entries_dbl(){ return(::qtable_dbl_entries(qt));}
	double exits_dbl()	{ return(::qtable_dbl_exits(qt));}
	double min_dbl()	{ return(::qtable_dbl_min(qt));}
	double max_dbl()	{ return(::qtable_dbl_max(qt));}
	double range_dbl()	{ return(::qtable_dbl_range(qt));}
	double initial_dbl(){ return(::qtable_dbl_initial(qt));}
	double current_dbl(){ return(::qtable_dbl_current(qt));}
	double value_sum()	{ return(::qtable_qtsum(qt)); }
	double sum_square()	{ return(::qtable_sum_square(qt));}
	double mean()		{ return(::qtable_mean(qt));}
	double var()		{ return(::qtable_var(qt));}
	double stddev()		{ return(::qtable_stddev(qt));}
	double cv()			{ return(::qtable_cv(qt));}
	void set_name(const char* nm)	{ ::set_name_qtable(qt, nm); }
	void reset()		{ ::reset_qtable(qt); }

   /* JAB */
	
   long    hist_num ()                    { return (::qtable_histogram_num (qt)); }
   double  hist_low ()                    { return (::qtable_histogram_low (qt)); }
   double  hist_high ()                   { return (::qtable_histogram_high (qt)); }
   double  hist_width ()                  { return (::qtable_histogram_width (qt)); }
   double  hist_total ()                  { return (::qtable_histogram_total (qt)); }
   double  hist_bucket (long i)           { return (::qtable_histogram_bucket (qt, i)); }

   double    batch_size ()                  { return (::qtable_batch_size (qt)); }
   long    batch_count ()                 { return (::qtable_batch_count (qt)); }
   long converged ()                   { return (::qtable_converged (qt)); }
   double  conf_mean ()                   { return (::qtable_conf_mean (qt)); }
   double  conf_halfwidth (double level)  { return (::qtable_conf_halfwidth (qt, level)); }
   double  conf_lower (double level)      { return (::qtable_conf_lower (qt, level)); }
   double  conf_upper (double level)      { return (::qtable_conf_upper (qt, level)); }
   double  conf_accuracy (double level)   { return (::qtable_conf_accuracy (qt, level)); }

	long cnt()			{ return(::qtable_cnt(qt)); }
	long cur()			{ return(::qtable_cur(qt)); }
	long size()			{ return(::qtable_window_size(qt)); }
	double qlen()		{ return(::qtable_qlen(qt)); }
	double qtime()		{ return(::qtable_qtime(qt)); }
	double current_state()	{ return(::current_state(qt)); }	/* JAB */
	void set_moving(long n)	{ ::set_moving_qtable(qt, n); }
};


class qhistogram : public csim_qtable {
	struct histo *h;
public:
	qhistogram(const char *nm, long n) : csim_qtable(nm, n+1, 0L, n) {}
	qhistogram(const char *nm, long n, long lo, long hi) : csim_qtable(nm, n+1, lo, hi) {}
   long    num ()                    { return (::qtable_histogram_num (qt)); }
   double  low ()                    { return (::qtable_histogram_low (qt)); }
   double  high ()                   { return (::qtable_histogram_high (qt)); }
   double  width ()                  { return (::qtable_histogram_width (qt)); }
   double  total ()                  { return (::qtable_histogram_total (qt)); }
   double  bucket (long i)           { return (::qtable_histogram_bucket (qt, i)); }
};

class csim_meter {
protected:
	METER m;
	csim_table *t;
public:
	csim_meter(const char *nm)		{ m = create_meter(nm); t = new csim_table((csim_table*)meter_ip_table(m)); }
	csim_meter()				{ m = create_meter("def"); t = new csim_table((csim_table*)meter_ip_table(m));}
	~csim_meter()			{if(m != NIL) {::delete_meter(m); m = NIL;} }
	void note_passage()	{ ::note_passage(m);}
	void report()		{ report_meter(m);}
	void add_histogram(long n, double lo, double hi)
			{t->add_histogram(n, lo, hi);}
	void confidence()	{ meter_confidence(m);}
	void run_length(double ac, double clev, double runtm)
		{meter_run_length(m, ac, clev, runtm);}
	const char *name()		{ return(meter_name(m)); }
	double start_time()	{ return(meter_start_time(m));}
	long cnt()			{ return(meter_cnt(m));}
	double rate()		{ return(meter_rate(m));}
	csim_table* ip_table()	{ return(t);}
	void set_name(const char *nm) { set_name_meter(m, nm);}
	void reset()		{ reset_meter(m);}
};

class csim_box {
protected:
	BOX b;
	csim_table *t;
	csim_qtable *qt;
public:
	csim_box(const char *nm)	{ b = create_box(nm); t = new csim_table((csim_table*)box_time_table(b));
			qt = new csim_qtable((csim_qtable*)box_number_qtable(b)); }
	csim_box() { b = create_box("def"); t = new csim_table((csim_table*)box_time_table(b));
			qt = new csim_qtable((csim_qtable*)box_number_qtable(b));}
	~csim_box()			{if(b != NIL) {::delete_box(b); b = NIL;}}
	double enter()	{ return(enter_box(b));}
	void exit(double et)	{ exit_box(b, et);}
	void report()	{ report_box(b);}
	void add_time_histogram(long n, double mn, double mx)
			{t->add_histogram(n, mn, mx); }
	void add_number_histogram(long n, long lo, long hi)
			{qt->add_histogram(n, lo, hi);}
	void time_confidence()	{ box_time_confidence(b);}
	void number_confidence(){ box_number_confidence(b);}
	void time_run_length(double ac, double clev, double runtm) {
		box_time_run_length(b, ac, clev, runtm);}
	void number_run_length(double ac, double clev, double runtm) {
		box_number_run_length(b, ac, clev, runtm);}
	void time_moving_window(long n) { box_time_moving_window(b, n);}
	void number_moving_window(long n) { box_number_moving_window(b, n);}
	const char *name()	{ return(box_name(b));}
	csim_table* time_table()	{ return(t);}
	csim_qtable* number_qtable() { return(qt);}
	void set_name(const char *nm)	{ set_name_box(b, nm);}
	void reset()		{ reset_box(b);}
};	

class csim_stream {
protected:
	void* s;
	STREAM1 s1;
	STREAM2 s2;
public:
	csim_stream(long n)			{ s1 = stream_init1(n); s = s1; s2 = NIL;}
	csim_stream()				{ s1 = create_stream1();s = s1; s2 = NIL;}
	csim_stream(STREAM1 ss)		{s1 = create_stream1(); s = s1; s2 = NIL;}
	csim_stream(STREAM2 ss)		{s2 = create_stream2();	s = s2; s1 = NIL;}
	~csim_stream()				{if(s1 != NIL) delete_stream1(s1); else if(s2 != NIL) delete_stream2(s2);}
	void reseed(long n)			{if(s1 != NIL) ::reseed1((STREAM1)s, n);}
	long state()	{ return stream_state1((STREAM1)s);}
	void reseed2(long n1, long n2)	{ ::reseed2(s2, n1, n2);}
	void state2(long *n1, long *n2)	{ stream_state2(s2, n1, n2);}
	double erlang(double u, double v) { return(::stream_erlang(s, u, v)); }
	double expntl(double x)		{ return(::stream_expntl(s, x)); }
	double hyperx(double u, double v) { return(::stream_hyperx(s, u, v)); }
#ifndef MAC
#ifndef MAC_PPC
	double normal(double u, double std) { return(::stream_normal(s, u, std)); }
#else
	double x_normal(double u, double std) { return(::stream_normal(s, u, std)); }
#endif
#else
	double x_normal(double u, double std) { return(::stream_normal(s, u, std)); }
#endif
	long random(long i1, long i2)	{ return(::stream_uniform_int(s, i1, i2)); }
	long random_int(long i1, long i2) { return(::stream_uniform_int(s, i1, i2)); }
	double prob()			{ return(::stream_prob(s)); }
	void reset_prob(long n)	{ ::stream_reset_prob1(s1, n); }
	double uniform(double x1, double x2) {return(::stream_uniform(s, x1, x2)); }
	
	/* JAB additions */
	
	double uniform01 ( )     { return (::stream_uniform01 (s)); }
	double triangular (double minimum, double maximum, double mode)
	                         { return (::stream_triangular (s, minimum, maximum, mode)); }
	double gamma (double mean, double stddev)
	                         { return (::stream_gamma (s, mean, stddev)); }
	double exponential (double mean)
	                         { return (::stream_exponential (s, mean)); }
	double erlang2 (double mean, double var)
	                         { return (::stream_erlang2 (s, mean, var)); }
	double erlangn (double mean, long n)
							{return (::stream_erlangn(s, mean, n)); }
	double beta (double minimum, double maximum, double shape1, double shape2)
	                         { return (::stream_beta (s, minimum, maximum, shape1, shape2)); }
	double weibull (double shape, double scale)
	                         { return (::stream_weibull (s, shape, scale)); }
	double normal2 (double mean, double stddev)
	                         { return (::stream_normal2 (s, mean, stddev)); }
	double lognormal (double mean, double stddev)
	                         { return (::stream_lognormal (s, mean, stddev)); }
	double cauchy (double alpha, double beta)
	                         { return (::stream_cauchy (s, alpha, beta)); }
	double hypoexponential (double mn, double var)
							{return (::stream_hypoexponential (s, mn, var)); }
	double pareto(double a)
							{return (::stream_pareto(s, a));}
	long zipf(long n)
							{return (::stream_zipf(s, n)); }
	long zipf_sum(long n, double *sum)
							{return (::stream_zipf_sum(s, n, sum)); }
	long uniform_int (long minimum, long maximum)
	                         { return (::stream_uniform_int (s, minimum, maximum)); }
	long bernoulli (double probsuccess)
	                         { return (::stream_bernoulli (s, probsuccess)); }
	long binomial (double probsuccess, long numtrials)
	                         { return (::stream_binomial (s, probsuccess, numtrials)); }
	long geometric (double probsuccess)
	                         { return (::stream_geometric (s, probsuccess)); }
	long negative_binomial (long successnum, double probsuccess)
	                         { return (::stream_negative_binomial (s, successnum, probsuccess)); }
	long poisson (double mean)
	                         { return (::stream_poisson (s, mean)); }
	double empirical (const long n, double cutoff[], long alias[], const double value[])
                             { return (::stream_empirical (s, n, cutoff, alias, value)); }
};

class csim_stream2 : public csim_stream {
protected:
	STREAM2 s2;
public:
	csim_stream2()	{s2 = create_stream2(); s = s2; s1 = NIL; set_stream_prob2(stream_prob2);}
};

#ifdef CPP_MAIN
double expntl(double mean) {return (::stream_exponential (NIL, mean)); };
double erlang(double u, double v) {return(::stream_erlang(NIL, u, v)); }
//double expntl(double x)		{return(::stream_expntl(NIL, x)); }
double hyperx(double u, double v) {return(::stream_hyperx(NIL, u, v)); }
#ifndef MAC
#ifndef MAC_PPC
double normal(double u, double std) {return(::stream_normal(NIL, u, std)); }
#else
double x_normal(double u, double std) {return(::stream_normal(NIL, u, std)); }
#endif
#else
double x_normal(double u, double std) {return(::stream_normal(NIL, u, std)); }
#endif
long random(long i1, long i2)	{return(::stream_uniform_int(NIL, i1, i2)); }
long random_int(long i1, long i2) {return(::stream_uniform_int(NIL, i1, i2)); }
double prob()			{return(::stream_prob(NIL)); }
// void reset_prob(long n)	{::stream_reset_prob(NIL, n); }
double uniform(double x1, double x2) {return(::stream_uniform(NIL, x1, x2)); }	
/* JAB additions */
double uniform01( )     {return(::stream_uniform01 (NIL)); }
double triangular(double minimum, double maximum, double mode)
	                         {return(::stream_triangular (NIL, minimum, maximum, mode)); }
double gamma(double mean, double stddev)
	                         {return(::stream_gamma (NIL, mean, stddev)); }
double exponential(double mean)
	                         {return(::stream_exponential (NIL, mean)); }
double erlang2(double mean, double var)
	                         {return(::stream_erlang2 (NIL, mean, var)); }
double erlangn(double u, long n)
							{return(::stream_erlangn(NIL, u, n)); }
double beta(double minimum, double maximum, double shape1, double shape2)
	                         {return(::stream_beta (NIL, minimum, maximum, shape1, shape2)); }
double weibull(double shape, double scale)
	                         {return(::stream_weibull (NIL, shape, scale)); }
double normal2(double mean, double stddev)
	                         {return(::stream_normal2 (NIL, mean, stddev)); }
double lognormal(double mean, double stddev)
	                         {return(::stream_lognormal (NIL, mean, stddev)); }
double cauchy(double alpha, double beta)
	                         {return(::stream_cauchy (NIL, alpha, beta)); }
double hypoexponential(double mn, double var)
							{return (::stream_hypoexponential(NIL, mn, var)); }
double pareto(double a)
							{return (::stream_pareto(NIL, a));}
long zipf(long n)
							{return(::stream_zipf(NIL, n)); }
long zipf_sum(long n, double *sum)
							{return(::stream_zipf_sum(NIL, n, sum));}
long uniform_int(long minimum, long maximum)
	                         {return(::stream_uniform_int (NIL, minimum, maximum)); }
long bernoulli(double probsuccess)
	                         {return(::stream_bernoulli (NIL, probsuccess)); }
long binomial(double probsuccess, long numtrials)
	                         {return(::stream_binomial (NIL, probsuccess, numtrials)); }
long geometric(double probsuccess)
	                         {return(::stream_geometric (NIL, probsuccess)); }
long negative_binomial(long successnum, double probsuccess)
	                         {return(::stream_negative_binomial (NIL, successnum, probsuccess)); }
long poisson(double mean) {return(::stream_poisson (NIL, mean)); }
double empirical(const long n, double cutoff[], long alias[], const double value[])
                             {return(::stream_empirical (NIL, n, cutoff, alias, value)); }
#else
extern double expntl(double mean);
extern double erlang(double u, double v);
//extern double expntl(double x);
extern double hyperx(double u, double v);
#ifndef MAC
#ifndef MAC_PPC
extern double normal(double u, double std);
#else
extern double x_normal(double u, double std);
#endif
#else
extern double x_normal(double u, double std);
#endif
extern long random(long i1, long i2);
extern long random_int(long i1, long i2);
extern double prob();
extern void reset_prob(long n);
extern double uniform(double x1, double x2);	
/* JAB additions */	
extern double uniform01( );
extern double triangular(double minimum, double maximum, double mode);
extern double gamma(double mean, double stddev);
extern double exponential(double mean);
extern double erlang2(double mean, double var);
extern double erlangn(double mean, long n);
extern double beta(double minimum, double maximum, double shape1, double shape2);
extern double weibull(double shape, double scale);
extern double normal2(double mean, double stddev);
extern double lognormal(double mean, double stddev);
extern double cauchy(double alpha, double beta);
extern double hypoexponential(double mn, double var);
extern double pareto(double a);
extern long zipf(long n);
extern long zipf_sum(long n, double *sum);
extern long uniform_int(long minimum, long maximum);
extern long bernoulli(double probsuccess);
extern long binomial(double probsuccess, long numtrials);
extern long geometric(double probsuccess);
extern long negative_binomial(long successnum, double probsuccess);
extern long poisson (double mean);
extern double empirical(const long n, double cutoff[], long alias[], const double value[]);
#endif

extern csim_event converged;                                   /* JAB */
extern csim_event event_list_empty;
extern csim_event converged;
extern csim_event end_batch;
extern csim_event sim_terminated;
extern process_class default_class;
extern csim_event iem_go;
extern long iem_state;
extern long iem_prog_state;

// #define random(x, y) random_int(x, y)

#endif
