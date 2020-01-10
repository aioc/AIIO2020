#!/usr/bin/bash

set -e;

(cd 1-metropole/statement && make)
(cd 2-lbot/statement && make)
(cd 3-purview/statement && make)
