VAGRANTFILE_API_VERSION = "2"


Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

  config.vm.define :engine do |engine_config|

     engine_config.vm.box = "precise64-chef-puppet"
     engine_config.vm.box_url = "http://goo.gl/8kWkm"
     engine_config.vm.network "private_network", ip:"33.33.33.18"
     engine_config.vm.network :forwarded_port, guest: 80, host: 8095
     
     engine_config.vm.synced_folder ".", "/cookbooks"


     engine_config.vm.provider :virtualbox do |vb|
        vb.customize ["modifyvm", :id, "--cpuexecutioncap", "50"]
        vb.customize ["modifyvm", :id, "--ioapic", "on"]
      	vb.customize ["modifyvm", :id, "--memory", "4096"]
        vb.customize ["modifyvm", :id, "--cpus", "4"]
     end



     engine_config.vm.provision "chef_solo" do |chef|
    	chef.roles_path = "roles"
    	chef.add_role("appserver") 
     end

   end

end
