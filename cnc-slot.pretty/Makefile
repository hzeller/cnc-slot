
all : cnc-card-edge-25.kicad_mod cnc-card-edge-31.kicad_mod cnc-card-edge-36.kicad_mod

cnc-card-edge-25.kicad_mod: card-edge-gen
	./card-edge-gen 25 > $@

cnc-card-edge-31.kicad_mod: card-edge-gen
	./card-edge-gen 31 > $@

cnc-card-edge-36.kicad_mod: card-edge-gen
	./card-edge-gen 36 > $@

card-edge-gen: card-edge-gen.cc
