#include <stdio.h>                           /* standard I/O stuff */

#ifdef HAVE_CONFIG_H
    #include <config.h>                      /* for autotools */
#endif

#if STDC_HEADERS
    #include <stdlib.h>                      /* standard library stuff */
    #include <string.h>                      /* the string manip functs */
#endif

#if HAVE_UNISTD_H
    #include <unistd.h>                      /* used for sleep, optarg */
#endif

#if HAVE_SYS_TYPES_H
    #include <sys/types.h>                   /* open and read stuff */
#endif

#if HAVE_SYS_STAT_H
    #include <sys/stat.h>                    /* open and read stuff */
#endif

#if HAVE_ERRNO_H
    #include <errno.h>                       /* just for error codes */
#endif

#if HAVE_FCNTL_H
    #include <fcntl.h>                       /* for open() */
#endif

#if WITH_DMALLOC
    #include <dmalloc.h>                     /* for memory stats */
#endif

#define LINE_SIZE 80
#define NUM_ASCII 256
#define KAPPA_R .00391
#define DELTA_SCALE 20.00

static double KAPPA_P = .06721;
static double ALPHA = 85.00;
static double DELTA = 45.00;
static double DELTA_DATA[NUM_ASCII] = {
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.02159470613142943, 0.6285374239022192,
    0.000000000000000, 0.005185663688211039, 0.6133133535749141,
    0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.00003949907053044318, 0.000000000000000,
    18.22847120088911, 0.04859514220116809, 0.5461592909487992,
    0.003402562789979605, 0.002234518847150785, 0.001303469327504625,
    0.006477847566992680, 0.3059033730851979, 0.08960646286049109,
    0.09127106654713120, 0.007922385003534602, 0.09826240203101963,
    1.053056505790338, 0.4302746607368405, 1.376283042665316,
    0.09522661632453701, 0.1386530230105785, 0.1799069808174457,
    0.1202633843164765, 0.07334413125067149, 0.07575357455302852,
    0.06504368371491692, 0.09012559350174834, 0.04630419611040239,
    0.05494320710784645, 0.08418380474909740, 0.09928937786481117,
    0.03923386248545305, 0.01657832417406315, 0.01697895760372907,
    0.01933197366247119, 0.07915049461864664, 0.003537988174655410,
    0.2914128569248868, 0.1257424696714851, 0.1951649074909197,
    0.1386417375618555, 0.1284566200893627, 0.1055302310086212,
    0.06836724836383565, 0.2390822311964111, 0.3479924540975659,
    0.03624886129822385, 0.03771032690785025, 0.09399085968937028,
    0.1463158426934845, 0.1507735949390631, 0.1007395580257146,
    0.1932125248618435, 0.01100895522927066, 0.1581881347500634,
    0.2934780940411928, 0.3444883222690794, 0.05642724361491882,
    0.02919545584635900, 0.1236151625872027, 0.01430430625638192,
    0.05275947277994910, 0.004976882886835840, 0.03121555116777309,
    0.001004404936345555, 0.03118733754596563, 0.0005642724361491883,
    0.03387891706639726, 0.0006037715066796314, 5.687533235646489,
    1.065707493808803, 2.069813365763199, 2.943182956986189,
    9.018512424376208, 1.488669183773150, 1.553803151077851,
    3.836166658089726, 4.859497291943724, 0.07046634182631062,
    0.7000476697354059, 2.918490395180301, 1.663824990678219,
    5.016218318359800, 5.537707618400157, 1.403289121459416,
    0.06597473323456308, 4.474065361707660, 4.668818350320191,
    6.601158022464363, 2.045137732130395, 0.6983887087731273,
    1.398317881296942, 0.1526864784976088, 1.483483520084939,
    0.06741927067110501, 0.002584367757563282, 0.02536404600490601,
    0.002584367757563282, 0.0006489133015715664, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000,
    0.000000000000000, 0.000000000000000, 0.000000000000000, 0.000000000000000
};


/* function prototypes */
static void _usage(char *prog_name);
static void _xor(int fo, char *key, char *data, int data_size);
static void _ascii_decrypt(int fo, char *key, char *data, int data_size);
static void _get_kappa(int od, char *data, int data_size);
static void _break_ascii(int od, int fo, char *cyphertext, int c_size,
    int k_length);
static void _break_xor(int od, int fo, char *cyphertext, int c_size,
    int k_length);
static void _set_delta_data(char *data, int d_size);
static int _phi_test(int print, char *cyphertext, int c_size);
static double *_get_delta_data(char *data, int d_size);


int
main(int argc, char *argv[])
{
    int e_flag = 0, d_flag = 0, k_flag = 0,
        i_flag = 0, f_flag = 0, l_flag = 0,
        F_flag = 0, p_flag = 0, s_flag = 0,
        a_flag = 0, b_flag = 0, g_flag = 0,
        z_flag = 0, o_flag = 0;

    int opt;                                 /* used for getopt */
    int d_size = 0;                           /* the data size */
    int delta_size = 0;                       /* the delta data size */
    int di = 0;                              /* FD for delta file */
    int fi = 0;                              /* in file stream */
    int fo = 0;                              /* out file stream */
    int od = 0;                              /* data output file stream */
    int k_length = 0;                         /* length of key */
    char prog_name[256];                      /* the name of our program */
    char key[256];                           /* key */
    char *data = NULL;                       /* the data */
    char *dData = NULL;                      /* the delta data */
    struct stat file_info;                   /* for info on file */

    /* copy in case we need usage function */
    strncpy(prog_name, argv[0], sizeof(prog_name));

    if(argc <= 1)
    {
        _usage(prog_name);
        return(1);
    }

    /* loop until end of arg list */
    while((opt = getopt(argc, argv, "hedipbg:l:a:s:k:f:F:z:o:")) != EOF)
    {
        switch(opt)
        {
            case 'b':
                    b_flag++;
                break;

            case 'e':
                    e_flag++;
                break;

            case 'd':
                    d_flag++;
                break;

            case 'k':
                    strncpy(key, optarg, sizeof(key));
                    k_flag++;
                break;

            case 'i':
                    i_flag++;
                break;

            case 'p':
                    p_flag++;
                break;

            case 's':
                    KAPPA_P = atof(optarg);
                    s_flag++;
                break;

            case 'l':
                    k_length = atoi(optarg);
                    l_flag++;
                break;

            case 'a':
                    ALPHA = atof(optarg);
                    a_flag++;
                break;

            case 'z':
                    DELTA = atof(optarg);
                    z_flag++;
                break;

            case 'g':
                if((di = open(optarg, O_RDONLY)) == -1)
                {
                    fprintf(stderr, "open(): %s\n", strerror(errno));
                    return(1);
                }

                fstat(di, &file_info);
                dData = (char *)malloc(file_info.st_size);
                delta_size = read(di, dData, file_info.st_size);
                _set_delta_data(dData, delta_size);
                free(dData);
                close(di);
                g_flag++;
                break;

            case 'f':
                if((fi = open(optarg, O_RDONLY)) == -1)
                {
                    fprintf(stderr, "open(): %s\n", strerror(errno));
                    return(1);
                }

                fstat(fi, &file_info);
                data = (char *)malloc(file_info.st_size);
                d_size = read(fi, data, file_info.st_size);
                f_flag++;
                break;

            case 'F':
                if((fo = open(optarg, O_CREAT|O_WRONLY|O_TRUNC,
                    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1)
                {
                    fprintf(stderr, "open(): %s\n", strerror(errno));
                    return(1);
                }

                F_flag++;
                break;

            case 'o':
                if((od = open(optarg, O_CREAT|O_WRONLY|O_TRUNC,
                    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1)
                {
                    fprintf(stderr, "open(): %s\n", strerror(errno));
                    return(1);
                }

                o_flag++;
                break;

            default:
                _usage(prog_name);
                return(0);
                break;
        }
    }

    if((d_flag || e_flag) && f_flag && F_flag)
    {
        _xor(fo, key, data, d_size);
        close(fo);
    }
    else if(p_flag && f_flag && o_flag)
    {
        _get_kappa(od, data, d_size);
        close(od);
    }
    else if(i_flag && f_flag && o_flag)
    {
        _phi_test(od, data, d_size);
        free(data);
        close(od);
        return(0);
    }
    else if(b_flag && f_flag && F_flag && o_flag)
    {
        if(!(l_flag))
            k_length = _phi_test(od, data, d_size);

        _break_ascii(od, fo, data, d_size, k_length);
    }

    free(data);
    close(fi);
    return(0);
}


static void
_usage(char *prog_name)
{
    fprintf(stderr, "\nUsage: %s\n"
            "[-ihedpb] [-k <key>] [-f <input_file>] [-F <output_file>]\n"
            "[-s <KAPPA_P>] [-a <ALPHA>] [-l <key_length>] [-g <data_file>]\n"
            "[-z <DELTA>] [-o <output_data>]\n", prog_name);
    fprintf(stderr, "\n"
            "-h\tprint this usage message\n"
            "-e\tXOR encipher data\n"
            "-d\tXOR decipher data\n"
            "-b\tbreak xor cipher\n"
            "-l\tspecify the key length manually\n"
            "-i\tjust print index of coincidence information\n"
            "-k\tthe key used to encipher/decipher data\n"
            "-p\tget KAPPA_P value for some input file\n"
            "-s\tset the KAPPA_P value (default: .06721)\n"
            "-a\tset the ALPHA point for key length match (default: 85.00)\n"
            "-z\tset DELTA value probable plaintext match (default: 45.00)\n"
            "-g\tset delta data information\n"
            "-o\toutput data file name\n"
            "-f\tinput file name\n"
            "-F\toutput file name\n\n");
}


static void
_xor(int fo, char *key, char *data, int data_size)
{
    int i;
    char c;
    char *start_key = key;

    if(*key != '\0')
    {
        for(i = 0; i < data_size; i++)
        {
            if(!(*key))
                key = start_key;

            c = data[i] ^ *(key++);
            write(fo, &c, 1);
        }
    }
}


static void
_ascii_decrypt(int fo, char *key, char *data, int data_size)
{
    int i;
    char c;
    char *start_key = key;

    if(*key != '\0')
    {
        for(i = 0; i < data_size; i++)
        {
            if(!(*key))
                key = start_key;

            if (((data[i] - 32) - (*(key++) - 32)) >= 0)
                c = (((data[i] - 32) - (*(key++) - 32)) % 26) + 32;
            else
                c = 'Z';

            write(fo, &c, 1);
        }
    }
}


static int
_phi_test(int print, char *cyphertext, int c_size)
{
    int i;
    int key_length;
    int *cand_key = (int *)malloc(c_size * sizeof(int));
    double frequency[NUM_ASCII];
    double phi_r = 0.0;
    double phi_p = 0.0;
    double *match = (double *)malloc(c_size * sizeof(double));
    char line[LINE_SIZE];
    union idx_t { int i; char c; } idx;

    for(i = 0; i < c_size; i++)
        cand_key[i] = 0;

    for(i = 0; i < NUM_ASCII; i++)
        frequency[i] = 0;

    for(key_length = 1; key_length < c_size/2; key_length++)
    {
        for(i = 0; i < c_size; i += key_length)
        {
            memset(&idx, 0, sizeof(idx));
            idx.c = cyphertext[i];
            frequency[idx.i]++;
        }

        match[key_length] = 0;

        for(i = 0; i < NUM_ASCII; i++) 
        {
            match[key_length] += (frequency[i] * (frequency[i] - 1));
            frequency[i] = 0;
        }
    }

    snprintf(line, LINE_SIZE,
             "-------------------------------------------------------------\n");
    write(print, line, strlen(line));
    snprintf(line, LINE_SIZE, "%10s\t%10s\t%10s\t%10s\n",
             "Key Length", "PHI_R", "PHI_P", "Observed PHI");
    write(print, line, strlen(line));
    snprintf(line, LINE_SIZE,
             "-------------------------------------------------------------\n");
    write(print, line, strlen(line));

    for(key_length = 1; key_length < c_size/2; key_length++)
    {
        phi_r = KAPPA_R*(double)(c_size/key_length)*((c_size/key_length)-1);
        phi_p = KAPPA_P*(double)(c_size/key_length)*((c_size/key_length)-1);

        if((match[key_length] > phi_p) || ((match[key_length] > phi_r) &&
          ((match[key_length] - phi_r) > (phi_p - match[key_length])) &&
          ((100*(match[key_length]/phi_p)) > ALPHA)))
        {
            snprintf(line, LINE_SIZE,
                     "%10d\t%10.6g\t%10.6g\t%10.6g <=== Candidate\n",
                     key_length, phi_r, phi_p, match[key_length]);
            write(print, line, strlen(line));
            cand_key[key_length]++;
        }
        else
        {
            snprintf(line, LINE_SIZE,
                     "%10d\t%10.6g\t%10.6g\t%10.6g\n",
                     key_length, phi_r, phi_p, match[key_length]);
            write(print, line, strlen(line));
        }
    }

    for(i = 0; i < c_size/2; i++)
    {
        if(cand_key[i] >= 1)
        {
            key_length = i;
            break;
        }
    }

    snprintf(line, LINE_SIZE,
             "-------------------------------------------------------------\n");
    write(print, line, strlen(line));
    snprintf(line, LINE_SIZE, "Shortest Key Length is: %d\n", key_length);
    write(print, line, strlen(line));
    snprintf(line, LINE_SIZE,
             "-------------------------------------------------------------\n");
    write(print, line, strlen(line));
    fsync(print);

    return(key_length);
}

static void
_get_kappa(int od, char *data, int data_size)
{
    int i;
    double kappa_p = 0.0;
    double frequency[NUM_ASCII];
    char line[LINE_SIZE];

    for(i = 0; i < NUM_ASCII; i++)
        frequency[i] = 0.0;

    for(i = 0; i < data_size; i++)
         frequency[(int)data[i]]++;

    for(i = 0; i < NUM_ASCII; i++)
    {
        kappa_p += (frequency[i]/data_size) *
                   (frequency[i]/data_size);
    }

    snprintf(line, LINE_SIZE, "KAPPA_P for %d bytes is: %6.10g\n",
             data_size, kappa_p);
    write(od, line, strlen(line));
    fsync(od);
}


static void
_break_ascii(int od, int fo, char *cyphertext, int c_size, int k_length)
{
    int i;
    int j;
    int k;
    int x;
    int total_close;
    int data_size = (c_size/k_length) + 1;
    double (*cand_key)[NUM_ASCII] = malloc(k_length * sizeof(*cand_key));
    double *delta_info;
    double best_key;
    char line[LINE_SIZE];
    char *data = (char *)malloc(data_size);
    char *key = (char *)malloc(k_length + 1);

    memset(key, 0, (k_length + 1));

    for(i = 0; i < k_length; i++)
    {
        for(k = 0; k < NUM_ASCII; k++)
            cand_key[i][k] = 0.0;
    }

    for(i = 0; i < k_length; i++)
    {
        for(k = 32; k < NUM_ASCII; k++)
        {
            x = 0;

            for(j = i; j < c_size; j += k_length)
            {
                /* These values should be above 32 because they are
                   ascii plain text. */
                if (((cyphertext[j] - 32) - (k - 32)) >= 0)
                    data[x] = (((cyphertext[j] - 32) - (k - 32 )) % 26) + 32;
                else
                    data[x] = 0;

                x++;
            }

            delta_info = _get_delta_data(data, data_size);
            total_close = 0;

            for(j = 0; j < NUM_ASCII; j++)
            {
                if(DELTA_DATA[j] != delta_info[j])
                {
                    if(DELTA_DATA[j] < delta_info[j])
                    {
                        if((100 * (DELTA_DATA[j]/delta_info[j])) >= DELTA)
                            total_close++;
                    }
                    else
                    {
                        if((100 * (delta_info[j]/DELTA_DATA[j])) >= DELTA)
                            total_close++;
                    }
                }
                else
                    total_close++;
            }

            if((((double)total_close/NUM_ASCII) * 100) >= (DELTA + DELTA_SCALE))
                cand_key[i][k] = (((double)total_close/NUM_ASCII) * 100);

            free(delta_info);
        }
    }

    snprintf(line, LINE_SIZE,
             "-------------------------------------------------------------\n");
    write(od, line, strlen(line));
    snprintf(line, LINE_SIZE, "Possible values for each key position are:\n");
    write(od, line, strlen(line));
    snprintf(line, LINE_SIZE,
             "-------------------------------------------------------------\n");
    write(od, line, strlen(line));

    for(i = 0; i < k_length; i++)
    {
        snprintf(line, LINE_SIZE, "%d: ", i + 1);
        write(od, line, strlen(line));
        best_key = 0.0;

        for(j = 0; j < NUM_ASCII; j++)
        {
            if(cand_key[i][j] > best_key)
            {
                if(j >= 32 && j < 127)
                {
                    snprintf(line, LINE_SIZE, "%c ", j);
                    write(od, line, strlen(line));
                }
                else
                {
                    snprintf(line, LINE_SIZE, " 0x%hhx ", j);
                    write(od, line, strlen(line));
                }

                best_key = cand_key[i][j];
            }
        }

        for(j = 0; j < NUM_ASCII; j++)
        {
            if(cand_key[i][j] == best_key)
                key[i] = (char)j;
        }

        snprintf(line, LINE_SIZE, "\n");
        write(od, line, strlen(line));
    }

    snprintf(line, LINE_SIZE,
             "-------------------------------------------------------------\n");
    write(od, line, strlen(line));
    snprintf(line, LINE_SIZE, "Most probable key is: ");
    write(od, line, strlen(line));

    for(i = 0; i < k_length; i++)
    {
        if(key[i] >= 32 && key[i] < 127)
        {
            snprintf(line, LINE_SIZE, "%c", key[i]);
            write(od, line, strlen(line));
        }
        else
        {
            snprintf(line, LINE_SIZE, "%c", key[i] + 32);
            write(od, line, strlen(line));
        }
    }

    snprintf(line, LINE_SIZE,
           "\n-------------------------------------------------------------\n");
    write(od, line, strlen(line));
    fsync(od);

    _ascii_decrypt(fo, key, cyphertext, c_size);

    free(cand_key);
    free(data);
    free(key);
}


static void
_break_xor(int od, int fo, char *cyphertext, int c_size, int k_length)
{
    int i;
    int j;
    int k;
    int x;
    int total_close;
    int data_size = (c_size/k_length) + 1;
    double (*cand_key)[NUM_ASCII] = malloc(k_length * sizeof(*cand_key));
    double *delta_info;
    double best_key;
    char line[LINE_SIZE];
    char *data = (char *)malloc(data_size);
    char *key = (char *)malloc(k_length + 1);

    memset(key, 0, (k_length + 1));

    for(i = 0; i < k_length; i++)
    {
        for(k = 0; k < NUM_ASCII; k++)
            cand_key[i][k] = 0.0;
    }

    for(i = 0; i < k_length; i++)
    {
        for(k = 0; k < NUM_ASCII; k++)
        {
            x = 0;

            for(j = i; j < c_size; j += k_length)
            {
                data[x] = cyphertext[j] ^ k;
                x++;
            }

            delta_info = _get_delta_data(data, data_size);
            total_close = 0;

            for(j = 0; j < NUM_ASCII; j++)
            {
                if(DELTA_DATA[j] != delta_info[j])
                {
                    if(DELTA_DATA[j] < delta_info[j])
                    {
                        if((100 * (DELTA_DATA[j]/delta_info[j])) >= DELTA)
                            total_close++;
                    }
                    else
                    {
                        if((100 * (delta_info[j]/DELTA_DATA[j])) >= DELTA)
                            total_close++;
                    }
                }
                else
                    total_close++;
            }

            if((((double)total_close/NUM_ASCII) * 100) >= (DELTA + DELTA_SCALE))
                cand_key[i][k] = (((double)total_close/NUM_ASCII) * 100);

            free(delta_info);
        }
    }

    snprintf(line, LINE_SIZE,
             "-------------------------------------------------------------\n");
    write(od, line, strlen(line));
    snprintf(line, LINE_SIZE, "Possible values for each key position are:\n");
    write(od, line, strlen(line));
    snprintf(line, LINE_SIZE,
             "-------------------------------------------------------------\n");
    write(od, line, strlen(line));

    for(i = 0; i < k_length; i++)
    {
        snprintf(line, LINE_SIZE, "%d: ", i + 1);
        write(od, line, strlen(line));
        best_key = 0.0;

        for(j = 0; j < NUM_ASCII; j++)
        {
            if(cand_key[i][j] > best_key)
            {
                if(j >= 32 && j < 127)
                {
                    snprintf(line, LINE_SIZE, "%c ", j);
                    write(od, line, strlen(line));
                }
                else
                {
                    snprintf(line, LINE_SIZE, "0x%hhx ", j);
                    write(od, line, strlen(line));
                }

                best_key = cand_key[i][j];
            }
        }

        for(j = 0; j < NUM_ASCII; j++)
        {
            if(cand_key[i][j] == best_key)
                key[i] = (char)j;
        }

        snprintf(line, LINE_SIZE, "\n");
        write(od, line, strlen(line));
    }

    snprintf(line, LINE_SIZE,
             "-------------------------------------------------------------\n");
    write(od, line, strlen(line));
    snprintf(line, LINE_SIZE, "Most probable key is: ");
    write(od, line, strlen(line));

    for(i = 0; i < k_length; i++)
    {
        if(key[i] >= 32 && key[i] < 127)
        {
            snprintf(line, LINE_SIZE, "%c", key[i]);
            write(od, line, strlen(line));
        }
        else
        {
            snprintf(line, LINE_SIZE, " 0x%hhx ", key[i]);
            write(od, line, strlen(line));
        }
    }

    snprintf(line, LINE_SIZE,
           "\n-------------------------------------------------------------\n");
    write(od, line, strlen(line));
    fsync(od);

    _xor(fo, key, cyphertext, c_size);

    free(cand_key);
    free(data);
    free(key);
}


static double *
_get_delta_data(char *data, int d_size)
{
    int i;
    int *frequency = (int *)malloc(NUM_ASCII * sizeof(int));
    double *delta_info = (double *)malloc(NUM_ASCII * sizeof(double));
    union idx_t { int i; char c; } idx;

    for(i = 0; i < NUM_ASCII; i++)
        frequency[i] = 0;

    for(i = 0; i < d_size; i++)
    {
        memset(&idx, 0, sizeof(idx));
        idx.c = data[i];
        frequency[idx.i]++;
    }

    for(i = 0; i < NUM_ASCII; i++)
        delta_info[i] = (double)frequency[i]/d_size * 100;

    free(frequency);
    return(delta_info);
}


static void
_set_delta_data(char *data, int d_size)
{
    int i;
    int	*frequency = (int *)malloc(NUM_ASCII * sizeof(int));
    union idx_t { int i; char c; } idx;

    for(i = 0; i < NUM_ASCII; i++)
        frequency[i] = 0;

    for(i = 0; i < d_size; i++)
    {
        memset(&idx, 0, sizeof(idx));
        idx.c = data[i];
        frequency[idx.i]++;
    }

    for(i = 0; i < NUM_ASCII; i++)
        DELTA_DATA[i] = (double)frequency[i]/d_size * 100;

    free(frequency);
}
