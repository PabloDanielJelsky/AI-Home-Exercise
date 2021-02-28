# Digital Terrain Model (DTM) - represents the elevation of the ground
# Digital Surface Model (DSM) - represents the elevation of the tallest surfaces at that point



#library(tiff)
library(sp)
# work with raster data
library(raster)
# export GeoTIFFs and other core GIS functions
library(rgdal)
library(ggplot2)
library(dplyr)
# Set the working directory
setwd ("/home/pablo/Documents/Software Engineering/AI home exercise/Input/")


# Use stack function to read in all bands
data <- stack("cage6.tif")

# view raster attributes
data@layers

getGDALVersionInfo()
gdalObject <- GDAL.open("cage6.tif")
GDALinfo("cage6.tif")
GDALSpatialRef("cage6.tif")
readGDAL("cage6.tif")
GDALis3ormore()
GDAL_OSR_PROJ()

# read a sample file (R logo)
#img <- readTIFF(system.file("img", "cage6.tif", package="tiff"))
#img <- readTIFF("cage6.tif", native = TRUE, info = TRUE)


GDALinfo("cage6.tif")
HARV_dsmCrop_info <- capture.output(
  GDALinfo("cage6.tif")
)
DSM_HARV <- raster("cage6.tif")
summary(DSM_HARV)
DSM_HARV_df <- as.data.frame(DSM_HARV, xy = TRUE)
str(DSM_HARV_df)
ggplot() +
  geom_raster(data = DSM_HARV_df , aes(x = x, y = y)) +
  scale_fill_viridis_c() +
  coord_quickmap()