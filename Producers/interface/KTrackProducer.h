/* Copyright (c) 2010 - All Rights Reserved
 *   Danilo Piparo <danilo.piparo@cern.ch>
 *   Fred Stober <stober@cern.ch>
 *   Manuel Zeise <zeise@cern.ch>
 */

#ifndef KAPPA_TRACKPRODUCER_H
#define KAPPA_TRACKPRODUCER_H

#include "KBaseMultiLVProducer.h"
#include <DataFormats/JetReco/interface/CaloJet.h>
#include <DataFormats/METReco/interface/HcalNoiseRBX.h>
#include <DataFormats/TrackReco/interface/Track.h>

class KTrackProducer : public KBaseMultiLVProducer<edm::View<reco::Track>, KDataTracks>
{
public:
	KTrackProducer(const edm::ParameterSet &cfg, TTree *_event_tree, TTree *_run_tree) :
		KBaseMultiLVProducer<edm::View<reco::Track>, KDataTracks>(cfg, _event_tree, _run_tree, getLabel()) {}

	static const std::string getLabel() { return "Tracks"; }

	virtual void fillSingle(const SingleInputType &in, SingleOutputType &out)
	{
		KTrackProducer::fillTrack(in, out);
	}

	// Static method for filling Tracks in other producers
	static void fillTrack(const SingleInputType &in, SingleOutputType &out)
	{
		// Momentum:
		out.p4.SetCoordinates(in.pt(), in.eta(), in.phi(), 0);
		out.errPt = in.ptError();
		out.errEta = in.etaError();
		out.errPhi = in.phiError();

		// Reference point:
		out.ref = in.referencePoint();

		// Charge, ...
		out.charge = in.charge();
		out.chi2 = in.chi2();
		out.nDOF = in.ndof();
		out.quality = in.qualityMask();
		out.errDxy = in.dxyError();
		out.errDz = in.dzError();

		out.nValidPixelHits = in.hitPattern().numberOfValidPixelHits();
		out.nValidStripHits = in.hitPattern().numberOfValidStripHits();
		out.nValidMuonHits = in.hitPattern().numberOfValidMuonHits();
		out.nLostMuonHits = in.hitPattern().numberOfLostMuonHits();
		out.nBadMuonHits = in.hitPattern().numberOfBadMuonHits();
		out.nValidHits = in.hitPattern().numberOfValidHits();
		out.nLostHits = in.hitPattern().numberOfLostHits();
		out.nPixelLayers = in.hitPattern().pixelLayersWithMeasurement();
		out.nStripLayers = in.hitPattern().trackerLayersWithMeasurement();
		// todo: check which of the two is needed for the e ID
		out.nInnerHits = in.trackerExpectedHitsInner().numberOfHits();
		out.nLostInnerHits = in.trackerExpectedHitsInner().numberOfLostHits();
	}
};

#endif
