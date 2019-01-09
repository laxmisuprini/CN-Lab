BEGIN{
fp=0;
fs=0;
cs=0;
cp=0;
}
{
event=$1;
pt=$5;
ps=$6;

if(event=="r" && pt=="tcp")
{
fp++;
fs=ps;
}

if(event=="r" && pt=="cbr")
{
cp++;
cs=ps;
}
}

END{
totalftp=fp*fs;
totalcbr=cp*cs;
print("throughput of ftp is%d bytes/sec\n"totalftp/123.0);
}


