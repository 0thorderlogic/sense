#!/bin/bash
python web_scrapping.py
cat scraped_text.txt
python send_to_ard.py
