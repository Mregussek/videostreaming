#!/bin/bash

raspivid -t 999999 -o – | nc $1 3305
