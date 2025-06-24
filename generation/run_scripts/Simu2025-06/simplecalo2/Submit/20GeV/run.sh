#!/bin/bash
hostname
cat /etc/os-release
source /home/llr/ilc/shi/code/SiWECAL-Prototype/generation/run_scripts/Simu2025-06/env.sh
ddsim --steeringFile /home/llr/ilc/shi/code/SiWECAL-Prototype/generation/run_scripts/Simu2025-06/simplecalo2/Submit/20GeV/sc2SteeringFile.py
