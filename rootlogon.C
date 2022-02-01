{
  printf("executing /afs/cern.ch/work/v/vveckaln/private/CMSSW_9_4_11/src/TopLJets2015/TopAnalysis/rootlogon.C\n");
  gSystem -> Load("libGraf.so");
  gSystem -> Load("libPhysics.so");
  gInterpreter -> AddIncludePath(gSystem -> ExpandPathName("${CFAT}/interface"));
  gSystem -> AddDynamicPath(gSystem -> ExpandPathName("${CFAT}/lib"));
  gSystem -> Load(gSystem -> ExpandPathName("${CFAT}/lib/libcfat.so"));
   
}
