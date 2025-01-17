source /home/llr/ilc/shi/code/ILC/ILCsoft.sh

__conda_setup="$('/home/llr/ilc/boudry/miniconda3/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "/home/llr/ilc/boudry/miniconda3/etc/profile.d/conda.sh" ]; then
        . "/home/llr/ilc/boudry/miniconda3/etc/profile.d/conda.sh"
    else
        export PATH="/home/llr/ilc/boudry/miniconda3/bin:$PATH"
    fi
fi
unset __conda_setup

