#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Feb 18 19:53:56 2021

@author: pablo
"""
import rasterio
from rasterio.plot import show

fp = r'/home/pablo/Documents/Software Engineering/AI Exercise/cage6.tif'
img = rasterio.open(fp)
show(img)