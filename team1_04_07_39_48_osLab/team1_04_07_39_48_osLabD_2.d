#!/usr/sbin/dtrace -s

dtrace:::BEGIN
{
	printf("              UID        GID\n");
	printf("uid entered: %d\n", $1);
}

syscall::write:entry
/(execname == "a.out" || execname == "output1" || execname == "output2" || execname == "kilo") && uid == $1/
{
	printf("%s", stringof(copyin(arg1, arg2)));
}

proc:::exec-success
/ uid == $1 /
{
	trace(curpsinfo->pr_psargs);
}

syscall::read:entry
/ (execname == "a.out" || execname == "output1" || execname == "output2" || execname == "kilo") && uid == $1/
{
	@[execname] = quantize(arg2);
}
