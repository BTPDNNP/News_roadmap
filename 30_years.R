library("xts")
library("tseries")
library("quantmod")
GSPC <- as.xts(get.hist.quote("^BSESN",start="2003-07-14",quote=c("Open","High","Low","Close","Volume")))
head(GSPC)
myATR <- function(x) ATR(HLC(x))[, "atr"]
mySMI <- function(x) SMI(HLC(x))[, "SMI"]
myADX <- function(x) ADX(HLC(x))[, "ADX"]
myAroon <- function(x) aroon(x[, c("High", "Low")])$oscillator
myBB <- function(x) BBands(HLC(x))[, "pctB"]
myChaikinVol <- function(x) Delt(chaikinVolatility(x[, c("High","Low")]))[, 1]

myCLV <- function(x) EMA(CLV(HLC(x)))[, 1]
#myEMV <- function(x) EMV(x[, c("High", "Low")], x[, "Volume"])[,2]

myMACD <- function(x) MACD(Cl(x))[, 2]
myMFI <- function(x) MFI(x[, c("High", "Low", "Close")],x[, "Volume"])

mySAR <- function(x) SAR(x[, c("High", "Close")])[, 1]
myVolat <- function(x) volatility(OHLC(x), calc = "garman")[,1]
T.ind <- function(quotes, tgt.margin = 0.025, n.days = 5) 
{ 
  
  v <- apply(HLC(quotes), 1, mean) 
  r <- matrix(NA, ncol = n.days, nrow = NROW(quotes)) 
  for (x in 1:n.days)
  {  
    r[, x] <- Next(Delt(Cl(quotes),v, k = x), x) 
    
  }
  
  x <- apply(r, 1, function(x) sum(x[x > tgt.margin | x < -tgt.margin])) 
  if (is.xts(quotes))  xts(x, time(quotes)) else x 
}

Delt.roughfix <- na.roughfix(Delt(Cl(GSPC),k=1:10))
ATR.roughfix <- na.roughfix( myATR(GSPC))
SMI.roughfix <- na.roughfix( mySMI(GSPC))
ADX.roughfix <- na.roughfix( myADX(GSPC))
Aroon.roughfix <- na.roughfix( myAroon(GSPC))
BB.roughfix <- na.roughfix(  myBB(GSPC))
Chai.roughfix <- na.roughfix( myChaikinVol(GSPC))
CLV.roughfix <- na.roughfix(myCLV(GSPC))
CMO.roughfix <- na.roughfix(CMO(Cl(GSPC)))
EMA.roughfix <- na.roughfix( EMA(Delt(Cl(GSPC))))
#EMV.roughfix <- na.roughfix( myEMV(GSPC))
VOL.roughfix <- na.roughfix(myVolat(GSPC))
MACD.roughfix <- na.roughfix(myMACD(GSPC))
MFI.roughfix <- na.roughfix( myMFI(GSPC))
RSI.roughfix <- na.roughfix( RSI(Cl(GSPC)))
SAR.roughfix <- na.roughfix( mySAR(GSPC))
Mean.roughfix <- na.roughfix(runMean(Cl(GSPC)))
SD.roughfix <- na.roughfix(runSD(Cl(GSPC)))
TIND.roughfix <- na.roughfix(T.ind(GSPC))
#GSPC <- na.roughfix(GSPC)
data.model <- specifyModel(TIND.roughfix ~ Delt.roughfix +
                             ATR.roughfix + SMI.roughfix + ADX.roughfix + Aroon.roughfix+
                             BB.roughfix + Chai.roughfix + CLV.roughfix+ 
                             CMO.roughfix + EMA.roughfix +  
                             VOL.roughfix + MACD.roughfix + MFI.roughfix + RSI.roughfix+
                             SAR.roughfix + Mean.roughfix + SD.roughfix)
rf <- buildModel(data.model,method='randomForest',training.per=c(start(GSPC), end(GSPC)),ntree=50, importance=T)
rf
varImpPlot(rf@fitted.model, type = 1)
imp <- importance(rf@fitted.model, type = 1)
rownames(imp)[which(imp > 8)]

