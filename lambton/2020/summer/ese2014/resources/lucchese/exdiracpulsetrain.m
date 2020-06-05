%% Reconstruction
Nv = [2 5 10 20];
fh = figure;
for i=1:length(Nv)
  rv = akv(kv==0)*ones(size(tv));
  for k=1:Nv(i)
    rv = rv + exp(j*pi/2*k*tv);
    rv = rv + exp(-j*pi/2*k*tv);
  end
  subplot(length(Nv),1,i);
  plot(tv,rv);  xlabel('t');  ylabel(sprintf('xr%i(t)',Nv(i)));
  %axis([-8 8 -0.5 1.5]);
end
exportfig(gcf,'exdiracpulsetrain.eps','width',5,'height',4.5,'fontmode','fixed','Color','cmyk','fontsize',8);
close(fh);

return;
