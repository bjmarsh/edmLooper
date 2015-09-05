{
    TFile f("myfile.root");
    
    TTree *Events = f.Get("Events");
    const int nevt = Events->GetEntries();
    //cout << "Number of events: " << nevt << endl;

    // have to do similar thing for any branch with a .obj sub-branch.
    // use Events->Print() to figure out class names
    edm::Wrapper< vector<reco::GenParticle> > *pWrapper = 0;
    vector<reco::GenParticle> *ps = 0;

    // example of a case where no wrapper is needed
    edm::EventAuxiliary *evtAux;

    // define branches. note that you do not include .obj
    TBranch *br_genps = Events->GetBranch("recoGenParticles_genParticles__SIM.");
    TBranch *br_evtaux = Events->GetBranch("EventAuxiliary");
    

    // begin event loop
    for(int i=0; i<nevt; i++){

        // must put these inside of loop! In theory shouldn't matter, because it sets to the same
        // address every time. However, after 3 hours of seg faults, it was determined that pointers
        // to pointers (eg ->mother()->pdgId()) point to the wrong thing for all events after the
        // first one if these statements are put outside of loop (wtf?)
        bevtaux->SetAddress(&evtAux);
        bgenps->SetAddress(&pWrapper);

        // load current event into the objects defined above
        Events->GetEntry(i);

        //finally, get the .obj object from the wrapper
        ps = pWrapper->product();

        int evtNo = evtAux->event();

        // now we can loop over particles!
        int np = ps->size();
        for(int j=0; j<np; j++){

            reco::GenParticle p = ps->at(j);
            //cout << evtNo << "\t" << j << "\t" << p.pdgId() << "\t" << p.status() << "\t" << p.mother()->pdgId() << "\t" << p.numberOfMothers() << "\t" << p.numberOfDaughters() << endl;


        }
        
    }
    
}
