#ifndef K_QP_H_
#define K_QP_H_

namespace K {
  class QP: public Klass {
    protected:
      void load() {
        json k = ((DB*)memory)->load(mMatter::QuotingParameters);
        if (k.empty()) return ((SH*)screen)->logWar("QP", "using default values for Quoting Parameters");
        *qp = k.at(0);
        ((SH*)screen)->log("DB", "loaded Quoting Parameters OK");
      };
      void waitUser() {
        ((UI*)client)->welcome(mMatter::QuotingParameters, &hello);
        ((UI*)client)->clickme(mMatter::QuotingParameters, &kiss);
      };
      void run() {
        delayUI();
      };
    private:
      function<void(json*)> hello = [&](json *welcome) {
        *welcome = { *qp };
      };
      function<void(json)> kiss = [&](json butterfly) {
        mQuotingParams prev(*qp);
        (*qp = butterfly).diff(prev);
        ((QE*)engine)->findMode("saved");
        ((MG*)market)->calcFairValue();
        ((PG*)wallet)->calcTargetBasePos();
        ((PG*)wallet)->calcSafety();
        ((MG*)market)->calcEwmaHistory();
        ((QE*)engine)->calcQuote();
        ((UI*)client)->send(mMatter::QuotingParameters, *qp);
        ((DB*)memory)->insert(mMatter::QuotingParameters, *qp);
        delayUI();
      };
      inline void delayUI() {
        ((UI*)client)->delayme(qp->delayUI);
      };
  };
}

#endif
